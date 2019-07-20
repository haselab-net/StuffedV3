#include "duktape_task.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <assert.h>
#include <duktape.h>
#include <stdlib.h>
#include <esp_system.h>

#include "duk_module_duktape.h"
#include "dukf_utils.h"
#include "duktape_utils.h"
#include "logging.h"
#include "modules.h"
#include "duk_alloc_hybrid.h"

#include "module_iot.h"

LOG_TAG("duktape_task");

// The heap context
duk_context *heap_context = NULL;
//	Threads
JSThread jsThreads[NJSTHREADS];
// mutex for heap
static xSemaphoreHandle heap_mutex = NULL;

void* duk_alloc_hybrid_udata = NULL;
/**
 * create environment for running js file
 */
static void createDuktapeHeap() {
    LOGD("About to create heap");
	//	Heap selection
#if 0
	heap_context = duk_create_heap_default();
#else
	if (!duk_alloc_hybrid_udata){
		duk_alloc_hybrid_udata = duk_alloc_hybrid_init();
	}
	heap_context = duk_create_heap(duk_alloc_hybrid, duk_realloc_hybrid, duk_free_hybrid, duk_alloc_hybrid_udata, NULL);
#endif

    if (!heap_context) { exit(1); }
    dukf_log_heap("Heap after duk create heap");
    
	duk_eval_string_noresult(heap_context, "new Function('return this')().Duktape = Object.create(Duktape);");

	duk_module_duktape_init(heap_context); // Initialize the duktape module functions.
	dukf_log_heap("Heap after duk_module_duktape_init");

	esp32_duktape_stash_init(heap_context); // Initialize the stash environment.

	registerModules(heap_context); // Register the built-in modules
	dukf_log_heap("Heap after duk register modules");

    dukf_runFile(heap_context, "/main/init.js");
    dukf_log_heap("Heap after init.js");

    #if defined(ESP_PLATFORM)
	    LOGD("Free heap at start of JavaScript main loop: %d", esp_get_free_heap_size());
    #endif /* ESP_PLATFORM */
}

static void processEvent(duk_context* ctx, esp32_duktape_event_t *pEvent) {
	duk_int_t callRc;
	LOGV(">> processEvent: eventType=%s", event_eventTypeToString(pEvent->type));

	switch(pEvent->type) {
		// Handle a new command line submitted to us.
		case ESP32_DUKTAPE_EVENT_COMMAND_LINE: {
			DUK_STACK_REMAIN(ctx);
			//LOGD("We are about to eval: %.*s", pEvent->commandLine.commandLineLength, pEvent->commandLine.commandLine);
			DUK_STACK_REMAIN(ctx);
			callRc = duk_peval_lstring(ctx,	pEvent->commandLine.commandLine, pEvent->commandLine.commandLineLength);
			DUK_STACK_REMAIN(ctx);
			// [0] - result
		    
			// If an error was detected, perform error logging.
			if (callRc != 0) {
				esp32_duktape_log_error(ctx);
			}

			// If we executed from a keyboard, send keyboard user response.
			if (pEvent->commandLine.fromKeyboard) {
				esp32_duktape_console(duk_safe_to_string(ctx, -1));
				esp32_duktape_console("\n");
				esp32_duktape_console("esp32_duktape> "); // Put out a prompt.
			}

			duk_pop(ctx); // Discard the result from the stack.
			// <Empty Stack>
			break;
		}

		case ESP32_DUKTAPE_EVENT_CALLBACK_REQUESTED: {
			// The event contains 4 properties:
			// * callbackType - int
			// * stashKey     - int - A key to an array stash that contains a function and parameters.
			// * context      - void * - a Duktape heapptr
			// * dataProvider - A function to be called that will add parameters to the stack.  If NULL, then
			//                  no data provider function is present.
			LOGD("Process a callback requested event: callbackType=%d, stashKey=%d",
				pEvent->callbackRequested.callbackType,
				pEvent->callbackRequested.stashKey
			);
			if (pEvent->callbackRequested.callbackType == ESP32_DUKTAPE_CALLBACK_TYPE_FUNCTION ||
					pEvent->callbackRequested.callbackType == ESP32_DUKTAPE_CALLBACK_TYPE_ISR_FUNCTION ||
					pEvent->callbackRequested.callbackType == ESP32_DUKTAPE_CALLBACK_STATIC_TYPE_FUNCTION) {

				int topStart = duk_get_top(ctx);

				// In this case, the stashKey points to a stashed array which starts with a callback function and parameters.
				esp32_duktape_unstash_array(ctx, pEvent->callbackRequested.stashKey);
				// [0] - function
				// [1] - param 1
				// [.] - param
				// [n] - param last

				int numberParams = duk_get_top(ctx) - topStart -1;

				LOGD("ESP32_DUKTAPE_EVENT_CALLBACK_REQUESTED: #params: %d", numberParams);

				if (!duk_is_function(ctx, topStart)) {
					LOGE("ESP32_DUKTAPE_EVENT_CALLBACK_REQUESTED: Not a function!");
					duk_pop_n(ctx, duk_get_top(ctx) - topStart);
					return;
				}

				if (pEvent->callbackRequested.dataProvider != NULL) {
					int numberAdditionalStackItems = pEvent->callbackRequested.dataProvider(ctx, pEvent->callbackRequested.context);
					numberParams += numberAdditionalStackItems;
				}

				duk_pcall(ctx, numberParams);
				// [0] - Ret val

				duk_pop(ctx);
				// <empty stack>
			}

			break;
		} // End of ESP32_DUKTAPE_EVENT_CALLBACK_REQUESTED

		default:
			LOGD("Unknown event type seen: %d", pEvent->type);
			break;
	} // End of switch
	LOGV("<< processEvent");
} // processEvent

void lock_heap() {
	xSemaphoreTake(heap_mutex, portMAX_DELAY);
}
void unlock_heap() {
	xSemaphoreGive(heap_mutex);
}

static void dukEventHandleTask(void* arg);

void duktape_start() {
	//	Initialize heap and threads
    dukf_init_nvs_values(); // Initialize any defaults for NVS data
    esp32_duktape_initEvents();
	if(!heap_mutex) heap_mutex = xSemaphoreCreateMutex();	// only create once
	lock_heap();
    if(!heap_context) createDuktapeHeap();					// only create once
	else {
		dukf_runFile(heap_context, "/main/reinit.js");
	}
	jsThreads[0].ctx = heap_context;
	for(int i=1; i<NJSTHREADS; ++i){
		// create new context on the same heap
		duk_push_thread(heap_context);
		jsThreads[i].ctx = duk_get_context(heap_context, -1);
	}
	unlock_heap();
	const char* taskNames[NJSTHREADS] = {"js0", "js1"};
	
	//	create tasks for threads
	for(int i=0; i<NJSTHREADS; ++i){
		xTaskCreate(dukEventHandleTask, taskNames[i], 1024*8, &jsThreads[i], tskIDLE_PRIORITY + 1, &jsThreads[i].task);
	}
	char* cmd = "ESP32.include('/main/runtime.js');";
	event_newCommandLineEvent(cmd, strlen(cmd), 0);
}

static void dukEventHandleTask(void* arg){
	JSThread* th = (JSThread*)arg;
	th->stackStart = (int)&th;
	th->stackPrev = 0;
	while(1){
		DUK_STACK_REMAIN(th->ctx);
		lock_heap();
		DUK_STACK_REMAIN(th->ctx);
		esp32_duktape_event_t* ev = malloc(sizeof(esp32_duktape_event_t));
		esp32_duktape_waitForEvent(ev);
		if (!th->ctx){
			unlock_heap();
			break;
		}
		DUK_STACK_REMAIN(th->ctx);
		processEvent(th->ctx, ev);
		DUK_STACK_REMAIN(th->ctx);
		esp32_duktape_freeEvent(th->ctx, ev);
		free(ev);
		DUK_STACK_REMAIN(th->ctx);
		unlock_heap();
	}
	TaskHandle_t t = th->task;
	th->task = NULL;
	vTaskDelete(t);
}

void duktape_end(){
	iotBeforeStopJSTask();
	for(int i=0; i<NJSTHREADS; ++i){
		jsThreads[i].ctx = NULL;
	}
	bool remain;
	do{
		remain = false;
		for(int i=0; i<NJSTHREADS; ++i){
			if (jsThreads[i].task){
				remain = true;
				char* cmd = ";";
				event_newCommandLineEvent(cmd, strlen(cmd), 0);
				vTaskDelay(1);
			} 
		}
	} while(remain);

	// delete heap
	lock_heap();
	duk_destroy_heap( heap_context );
	heap_context = NULL;
	unlock_heap();
	
	esp32_duktape_endEvents();
}

void duktape_print_stack_remain(duk_context* ctx, const char* at){
	JSThread* th = NULL;
	for(int i=0; i < NJSTHREADS; ++i){
		if (jsThreads[i].ctx == ctx){
			th = &jsThreads[i];
			int sd = th->stackStart-(int)&th;
			UBaseType_t ws = uxTaskGetStackHighWaterMark(th->task);
			printf("Stack: %+d = %d wm:%d at %s\n", sd-th->stackPrev, sd, ws, at);
			th->stackPrev = sd;

			//UBaseType_t sd = uxTaskGetStackHighWaterMark(th->task);
			//printf("Stack: %d at %s\n", (int)sd, at);

			break;
		}
	}
}
