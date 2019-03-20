#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <stdio.h>
#include <module_jsfile.h>

TaskHandle_t xHandle = NULL;

duk_context *esp32_duk_jsfile_context = NULL;

/**
 * stop running the current file
 */
static duk_ret_t stopFile(duk_context* ctx) {
    if( xHandle != NULL )
    {
        // delete task
        vTaskDelete( xHandle );
        xHandle = NULL;

        // destroy heap
        duk_destroy_heap( esp32_duk_jsfile_context );
        esp32_duk_jsfile_context = NULL;
    }

    return 0;
}

/**
 * run js file
 * [0] - file name
 */
static duk_ret_t runFile(duk_context* ctx) {
    const char *str;
    str = duk_get_string(ctx, -1);
    size_t str_len = duk_get_length(ctx, -1);

    // void* pvParameters = (void*)malloc(sizeof(size_t)+sizeof(char)*str_len);
    // memcpy(pvParameters, &str_len, sizeof(size_t));
    // memcpy(pvParameters+sizeof(size_t), str, str_len);

    duk_pop(ctx);

    if(!esp32_duk_jsfile_context) {
        createJSFileHeap();
    }

    void* pvParameters = malloc(0);

    //test(pvParameters);

    //xTaskCreate(runFileTask, "run_jsfile_task", 6*1024, pvParameters, tskIDLE_PRIORITY + 1, &xHandle);
    xTaskCreate(test, "test", 6*1024, NULL, tskIDLE_PRIORITY + 1, &xHandle);

    return 0;
}

/**
 * task for run file
 */
void runFileTask(void* pvParameters) {
    char *file_name;
    file_name = pvParameters+sizeof(size_t);

    printf("run file: %s\n", file_name);

    dukf_runFile(esp32_duk_jsfile_context, file_name);

    printf("end running file\n");
}

void test(void* pvParameters) {
    char *file_name = "main.js";
    printf("run file: %s\n", file_name);

    dukf_runFile(esp32_duk_jsfile_context, file_name);

    while(1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
        printf("wait 1s\n");
    }

    printf("end running file\n");
}

void createJSFileHeap() {
    if (esp32_duk_jsfile_context != NULL) {
		duk_destroy_heap(esp32_duk_jsfile_context);
	}

    LOGD("About to create jsfile heap");
    esp32_duk_jsfile_context = duk_create_heap_default();

    if (!esp32_duk_jsfile_context) { exit(1); }
    dukf_log_heap("Heap after duk create heap");
    
	duk_eval_string_noresult(esp32_duk_jsfile_context, "new Function('return this')().Duktape = Object.create(Duktape);");

	duk_module_duktape_init(esp32_duk_jsfile_context); // Initialize the duktape module functions.
	dukf_log_heap("Heap after duk_module_duktape_init");

	esp32_duktape_stash_init(esp32_duk_jsfile_context); // Initialize the stash environment.

	registerModules(esp32_duk_jsfile_context); // Register the built-in modules
	dukf_log_heap("Heap after duk register modules");

	dukf_runFile(esp32_duk_jsfile_context, "/init.js");	// Load and run the script called "init.js"

	dukf_log_heap("Heap after init.js");
}

/**
 * Add native methods to the JSFile object.
 */
duk_ret_t ModuleJSFile(duk_context *ctx) {
    ADD_FUNCTION("stop_file",   stopFile,  0);
    ADD_FUNCTION("run_file", runFile, 1);

    return 0;
}