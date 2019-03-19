#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <stdio.h>
#include <module_jsfile.h>

TaskHandle_t xHandle = NULL;

extern duk_context *esp32_duk_context;
duk_context *esp32_duk_jsfile_context = NULL;

/**
 * stop running the current file
 */
static duk_ret_t stopFile(duk_context* ctx) {
    if( xHandle != NULL )
    {
        vTaskDelete( xHandle );
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

    void* pvParameters = (void*)malloc(sizeof(size_t)+sizeof(char)*str_len);
    memcpy(pvParameters, &str_len, sizeof(size_t));
    memcpy(pvParameters+sizeof(size_t), str, str_len);

    duk_pop(ctx);

    if(!esp32_duk_jsfile_context) {
        (void)duk_push_thread(esp32_duk_context);
        esp32_duk_jsfile_context = duk_get_context(esp32_duk_context, -1);
    }
    xTaskCreate(runFileTask, "run_jsfile_task", 6*1024, pvParameters, tskIDLE_PRIORITY + 1, &xHandle);

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

/**
 * Add native methods to the JSFile object.
 */
duk_ret_t ModuleJSFile(duk_context *ctx) {
    ADD_FUNCTION("stop_file",   stopFile,  0);
    ADD_FUNCTION("run_file", runFile, 1);

    return 0;
}