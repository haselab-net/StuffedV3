#include "duktape_jsfile.h"

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

LOG_TAG("duktape_jsfile");

// The heap context
static duk_context *heap_context = NULL;
// The Duktape context.
duk_context *esp32_duk_context = NULL;
// mutex for heap
static xSemaphoreHandle heap_mutex = NULL;

// force to read from posix (espfs can not read the file altered in runtime)
static void runFileFromPosix(duk_context *ctx, const char *fileName) {
	LOGD(">> dukf_runFile: %s", fileName);
	size_t fileSize;

	char *fileData = dukf_loadFileFromPosix(fileName, &fileSize);
	if (fileData == NULL) {
		LOGE("<< dukf_runFile: Failed to load file");
		return;
	}
	// At this point we have the file in memory and we know its size.  Now we push it onto
	// the stack and run the script.
	duk_push_string(ctx, fileName);
	duk_compile_lstring_filename(ctx, 0, fileData, fileSize);

	free(fileData);
	fileData = NULL;

	int rc = duk_pcall(
		ctx,
		0 // Number of arguments
	);
	if (rc != 0) {
		esp32_duktape_log_error(ctx);
	}
	duk_pop(ctx);
	LOGD("<< dukf_runFile: %s", fileName);
}

static void runJsFile(){
	// run main.js
    runFileFromPosix(esp32_duk_context, "/spiffs/main/runtime.js");		// file in espfs would be rewrite from user
	ESP_LOGD(tag, "runtime.js finished.");
}

void* duk_alloc_hybrid_udata = NULL;
/**
 * create environment for running js file
 */
static void createJSFileHeap() {
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

static void processEvent(esp32_duktape_event_t *pEvent) {
	duk_int_t callRc;
	LOGV(">> processEvent: eventType=%s", event_eventTypeToString(pEvent->type));

	switch(pEvent->type) {
		// Handle a new command line submitted to us.
		case ESP32_DUKTAPE_EVENT_COMMAND_LINE: {
			LOGD("We are about to eval: %.*s", pEvent->commandLine.commandLineLength, pEvent->commandLine.commandLine);
			callRc = duk_peval_lstring(esp32_duk_context,	pEvent->commandLine.commandLine, pEvent->commandLine.commandLineLength);
			// [0] - result

    // If an error was detected, perform error logging.
			if (callRc != 0) {
				esp32_duktape_log_error(esp32_duk_context);
			}

			// If we executed from a keyboard, send keyboard user response.
			if (pEvent->commandLine.fromKeyboard) {
				esp32_duktape_console(duk_safe_to_string(esp32_duk_context, -1));
				esp32_duktape_console("\n");
				esp32_duktape_console("esp32_duktape> "); // Put out a prompt.
			}

			duk_pop(esp32_duk_context); // Discard the result from the stack.
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

				int topStart = duk_get_top(esp32_duk_context);

				// In this case, the stashKey points to a stashed array which starts with a callback function and parameters.
				esp32_duktape_unstash_array(esp32_duk_context, pEvent->callbackRequested.stashKey);
				// [0] - function
				// [1] - param 1
				// [.] - param
				// [n] - param last

				int numberParams = duk_get_top(esp32_duk_context) - topStart -1;

				LOGD("ESP32_DUKTAPE_EVENT_CALLBACK_REQUESTED: #params: %d", numberParams);

				if (!duk_is_function(esp32_duk_context, topStart)) {
					LOGE("ESP32_DUKTAPE_EVENT_CALLBACK_REQUESTED: Not a function!");
					duk_pop_n(esp32_duk_context, duk_get_top(esp32_duk_context) - topStart);
					return;
				}

				if (pEvent->callbackRequested.dataProvider != NULL) {
					int numberAdditionalStackItems = pEvent->callbackRequested.dataProvider(esp32_duk_context, pEvent->callbackRequested.context);
					numberParams += numberAdditionalStackItems;
				}

				duk_pcall(esp32_duk_context, numberParams);
				// [0] - Ret val

				duk_pop(esp32_duk_context);
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

void handle_event() {
    esp32_duktape_event_t esp32_duktape_event;

    // Process any events.  A return code other than 0 indicates we have an event.
    int rc = esp32_duktape_waitForEvent(&esp32_duktape_event);
    if (rc != 0) {
        processEvent(&esp32_duktape_event);
        esp32_duktape_freeEvent(esp32_duk_context, &esp32_duktape_event);
    }

    vTaskDelay(1);
}

void lock_heap() {
	xSemaphoreTake(heap_mutex, portMAX_DELAY);
}

void unlock_heap() {
	xSemaphoreGive(heap_mutex);
}

void duktape_start() {
    esp32_duktape_initEvents();

    dukf_init_nvs_values(); // Initialize any defaults for NVS data

	if(!heap_mutex) heap_mutex = xSemaphoreCreateMutex();	// only create once
	lock_heap();

    if(!heap_context) createJSFileHeap();					// only create once
	else {
		dukf_runFile(heap_context, "/main/reinit.js");
	}

	// create new context on the same heap
	(void*)duk_push_thread(heap_context);
	esp32_duk_context = duk_get_context(heap_context, -1);

    //duk_idx_t lastStackTop = duk_get_top(esp32_duk_context); // Get the last top value of the stack from which we will use to check for leaks.

	runJsFile();

	unlock_heap();
}

void duktape_end(){
    esp32_duktape_endEvents();

	esp32_duk_context = NULL;
	dukf_log_heap("Heap after set esp32_duk_context NULL");

    duk_destroy_heap( heap_context );
	heap_context = NULL;
}