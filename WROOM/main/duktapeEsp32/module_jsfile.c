/** 
 * start/stop task for running js file
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

#include <stdio.h>

#include <duktape.h>

#include "duk_module_duktape.h"
#include "dukf_utils.h"
#include "duktape_utils.h"
#include "module_jsfile.h"
#include "logging.h"
#include "modules.h"

#include "duktape_event.h"

extern void UdpCom_Lock_C();
extern void UdpCom_Unlock_C();

LOG_TAG("jsfile");

duk_context *esp32_duk_jsfile_context = NULL;

///////////////////////////////////
////////////// EVENT //////////////
///////////////////////////////////

// The maximum number of concurrent events we can have on the
// queue for processing.
#define MAX_EVENT_QUEUE_SIZE (20)

#if defined(ESP_PLATFORM)
static QueueHandle_t jsfile_event_queue; // The event queue (provided by FreeRTOS).
#endif /* ESP_PLATFORM */

static int stash_key_callback = 0;
static size_t return_packet_buffer_size;

static void jsfile_postEvent(esp32_duktape_event_t *pEvent, bool isISR) {
    #if defined(ESP_PLATFORM)
        if (isISR) {
            xQueueSendToBackFromISR(jsfile_event_queue, pEvent, NULL);
        } else {
            xQueueSendToBack(jsfile_event_queue, pEvent, portMAX_DELAY);
        }
    #else /* ESP_PLATFORM */
        assert(0);
    #endif  /* ESP_PLATFORM */
} // postEvent

static void jsfile_newCallbackRequestedEvent(
	uint32_t callbackType,
	uint32_t stashKey,
	esp32_duktape_callback_dataprovider dataProvider,
	void *contextData) {

	LOGD(">> jsfile_newCallbackRequestedEvent stashKey=%d", stashKey);
	esp32_duktape_event_t event;
	event.type = ESP32_DUKTAPE_EVENT_CALLBACK_REQUESTED;
	if (callbackType != ESP32_DUKTAPE_CALLBACK_TYPE_FUNCTION &&
			callbackType != ESP32_DUKTAPE_CALLBACK_TYPE_ISR_FUNCTION &&
			callbackType != ESP32_DUKTAPE_CALLBACK_STATIC_TYPE_FUNCTION) {
		LOGE("event_newCallbackRequestedEvent: Unknown callbackType: %d", callbackType);
		return;
	}
	event.callbackRequested.callbackType = callbackType;
	event.callbackRequested.stashKey     = stashKey;
	event.callbackRequested.dataProvider = dataProvider;
	event.callbackRequested.context      = contextData;
	if (callbackType == ESP32_DUKTAPE_CALLBACK_TYPE_ISR_FUNCTION) {
		jsfile_postEvent(&event, true);
	} else {
		jsfile_postEvent(&event, false);
	}
	LOGD("<< jsfile_newCallbackRequestedEvent");
} // event_newCallbackRequestedEvent

/**
 * Initialize the event handling.
 */
void jsfile_initEvents() {
	// Initialize the FreeRTOS queue.
    #ifdef ESP_PLATFORM
        jsfile_event_queue = xQueueCreate(MAX_EVENT_QUEUE_SIZE, sizeof(esp32_duktape_event_t));
    #endif
} // esp32_duktape_initEvents

/**
 * Stop the event handling
 */
void jsfile_stopEvents() {
    #ifdef ESP_PLATFORM
        vQueueDelete(jsfile_event_queue);
    #endif
}

/**
 * register callback for packet
 * [0] - callback function
 */
static duk_ret_t jsfile_register_packet_callback(duk_context* ctx){
    if(!duk_is_function(ctx, -1)) {
        LOGD("not a function");
        duk_pop(ctx);
        return DUK_RET_TYPE_ERROR;
    }

    if(stash_key_callback!=0) esp32_duktape_stash_delete(ctx, stash_key_callback);             // delete last registered callback

    stash_key_callback = esp32_duktape_stash_array(ctx, 1);

    if(stash_key_callback==0) LOGD("register callback failed");
    else LOGD("register callback success");

    return 0;
}

/**
 * Provide callback function with 2 parameters: buffer + buffersize
 */
static int return_packet_dataProvider(duk_context *ctx, void *context) {
    void* p = duk_push_buffer(ctx, return_packet_buffer_size, 0);
    memcpy(p, context, return_packet_buffer_size);
    duk_push_buffer_object(ctx, -1, 0, return_packet_buffer_size, DUK_BUFOBJ_ARRAYBUFFER);
    duk_replace(ctx, -2);
    duk_push_uint(ctx, return_packet_buffer_size);

    return 2;
}

/**
 * call the registered callback for packet
 */
void jsfile_exec_packet_callback(void* buffer, size_t buffer_size) {
    if(stash_key_callback==0) return;

    return_packet_buffer_size = buffer_size;

    jsfile_newCallbackRequestedEvent(
      ESP32_DUKTAPE_CALLBACK_STATIC_TYPE_FUNCTION,
      stash_key_callback, // Stash key for stashed callback array
      return_packet_dataProvider, // Data provider parameter
      buffer // Context parameter
   );
}

/**
 * read an event from queue and process it
 */
static duk_ret_t jsfile_handle_event(duk_context* ctx){
     esp32_duktape_event_t jsfile_event;

    /** wait for event */
    #if defined(ESP_PLATFORM)
	BaseType_t rc = xQueueReceive(jsfile_event_queue, &jsfile_event, 0);
    #else /* ESP_PLATFORM */
	int rc = 0;
    #endif /* ESP_PLATFORM */

    /** process event */
    if(rc!=0) {
        switch (jsfile_event.type)
        {
            case ESP32_DUKTAPE_EVENT_CALLBACK_REQUESTED:
                // The event contains 4 properties:
                // * callbackType - int
                // * stashKey     - int - A key to an array stash that contains a function and parameters.
                // * context      - void * - a Duktape heapptr
                // * dataProvider - A function to be called that will add parameters to the stack.  If NULL, then
                //                  no data provider function is present.
                LOGD("Process a callback requested event: callbackType=%d, stashKey=%d",
                    jsfile_event.callbackRequested.callbackType,
                    jsfile_event.callbackRequested.stashKey
                );
                if (jsfile_event.callbackRequested.callbackType == ESP32_DUKTAPE_CALLBACK_TYPE_FUNCTION ||
                        jsfile_event.callbackRequested.callbackType == ESP32_DUKTAPE_CALLBACK_TYPE_ISR_FUNCTION ||
                        jsfile_event.callbackRequested.callbackType == ESP32_DUKTAPE_CALLBACK_STATIC_TYPE_FUNCTION) {

                    int topStart = duk_get_top(esp32_duk_jsfile_context);

                    // In this case, the stashKey points to a stashed array which starts with a callback function and parameters.
                    esp32_duktape_unstash_array(esp32_duk_jsfile_context, jsfile_event.callbackRequested.stashKey);
                    // [0] - function
                    // [1] - param 1
                    // [.] - param
                    // [n] - param last

                    int numberParams = duk_get_top(esp32_duk_jsfile_context) - topStart -1;

                    LOGD("ESP32_DUKTAPE_EVENT_CALLBACK_REQUESTED: #params: %d", numberParams);

                    if (!duk_is_function(esp32_duk_jsfile_context, topStart)) {
                        LOGE("ESP32_DUKTAPE_EVENT_CALLBACK_REQUESTED: Not a function!");
                        duk_pop_n(esp32_duk_jsfile_context, duk_get_top(esp32_duk_jsfile_context) - topStart);
                        return DUK_RET_TYPE_ERROR;
                    }

                    if (jsfile_event.callbackRequested.dataProvider != NULL) {
                        int numberAdditionalStackItems = jsfile_event.callbackRequested.dataProvider(esp32_duk_jsfile_context, jsfile_event.callbackRequested.context);
                        numberParams += numberAdditionalStackItems;
                    }

                    duk_pcall(esp32_duk_jsfile_context, numberParams);
                    // [0] - Ret val

                    duk_pop(esp32_duk_jsfile_context);
                    // <empty stack>
                }
                break;
        
            default:
                LOGD("Unknown event type seen: %d", jsfile_event.type);
                break;
        }
    }

    vTaskDelay(1);

    return 0;
} 

///////////////////////////
/////// Task //////////////
///////////////////////////

TaskHandle_t xHandle = NULL;

/**
 * stop running the current file
 */
static duk_ret_t stopFile(duk_context* ctx) {
    LOGD(">> stop file");

    if( xHandle != NULL )
    {
        UdpCom_Lock_C();

        // delete task
        vTaskDelete( xHandle );
        xHandle = NULL;

        // destroy heap
        duk_destroy_heap( esp32_duk_jsfile_context );
        esp32_duk_jsfile_context = NULL;

        // stop event handling
        jsfile_stopEvents();

        UdpCom_Unlock_C();
    }

    LOGD("<< stop file");

    return 0;
}

/**
 * run js file
 */
static duk_ret_t runFile(duk_context* ctx) {
    jsfile_initEvents();
    
    if(!esp32_duk_jsfile_context) {
        createJSFileHeap();
    }

    xTaskCreate(runFileTask, "run_file_task", 6*1024, NULL, tskIDLE_PRIORITY + 1, &xHandle);

    return 0;
}

void runFileTask(void* pvParameters) {
    LOGD("Start runing JSFile");

    //dukf_runFile(esp32_duk_jsfile_context, "/main/main_init.js");
    dukf_runFile(esp32_duk_jsfile_context, "/main/main.js");
    //dukf_runFile(esp32_duk_jsfile_context, "/main/main_end.js");

    while(1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
        printf("wait 1s\n");
    }

    LOGD("End running JSFile");
}

/**
 * create environment for running js file
 */
void createJSFileHeap() {
    // initialize heap
    if (esp32_duk_jsfile_context != NULL) {
		duk_destroy_heap(esp32_duk_jsfile_context);
	}

    LOGD("About to create heap");
    esp32_duk_jsfile_context = duk_create_heap_default();

    if (!esp32_duk_jsfile_context) { exit(1); }
    dukf_log_heap("Heap after duk create heap");
    
	duk_eval_string_noresult(esp32_duk_jsfile_context, "new Function('return this')().Duktape = Object.create(Duktape);");

	duk_module_duktape_init(esp32_duk_jsfile_context); // Initialize the duktape module functions.
	dukf_log_heap("Heap after duk_module_duktape_init");

	esp32_duktape_stash_init(esp32_duk_jsfile_context); // Initialize the stash environment.

	registerModules(esp32_duk_jsfile_context); // Register the built-in modules
	dukf_log_heap("Heap after duk register modules");

    dukf_runFile(esp32_duk_jsfile_context, "/main/init.js");
    dukf_log_heap("Heap after init.js");

    #if defined(ESP_PLATFORM)
	    LOGD("Free heap at start of JavaScript main loop: %d", esp_get_free_heap_size());
    #endif /* ESP_PLATFORM */
}

 ////////////////////////
 //////// MODULE ////////
 ////////////////////////

/**
 * Add native methods to the JSFile object.
 */
duk_ret_t ModuleJSFile(duk_context *ctx) {
    ADD_FUNCTION("stop_file",   stopFile,   0);
    ADD_FUNCTION("run_file",    runFile,    0);    

    ADD_FUNCTION("register_callback",   jsfile_register_packet_callback,    1);
    ADD_FUNCTION("handle_event",        jsfile_handle_event,                0);

    return 0;
}