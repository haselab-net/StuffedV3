#include "ws_task.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "logging.h"

static TaskHandle_t* xHandle = NULL;

extern void duktape_main();

LOG_TAG("ws_task");

static void duktapeTask(void* pvParameters) {
    LOGD("Start running JSFile");

    duktape_main();

    LOGD("Finished running JSFile");

    while(1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
        printf("wait 1s\n");
    }
}

void wsCreateJsfileTask() {
    xTaskCreate(
        duktapeTask,
        "duktape_main",
        16*1024,
        NULL,
        tskIDLE_PRIORITY+1,
        xHandle
    );
}

void wsDeleteJsfileTask() {

}