#include "ws_task.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "esp_log.h"
extern "C" {
#include "../duktapeEsp32/include/duktape_jsfile.h"
#include "../duktapeEsp32/include/dukf_utils.h"
}
#include "../softRobot/UdpCom.h"
#include "duktape_jsfile.h"

static TaskHandle_t xHandle = NULL;

static char LOG_TAG[] = "ws_task";

static void duktapeTask(void* pvParameters) {
    ESP_LOGD(LOG_TAG, "Start running JSFile");

    dukf_log_heap("Heap after create task");

    duktape_start();

    ESP_LOGD(LOG_TAG, "Finished running JSFile");

    while(1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
        ESP_LOGD(LOG_TAG,"wait 1s");
    }
}

void wsCreateJsfileTask() {
    ESP_LOGD(LOG_TAG, "Create new jsfile task");

    dukf_log_heap("Heap before create task");

    BaseType_t xReturned = xTaskCreate(
        duktapeTask,
        "js_task",
        1024*12,
        NULL,
        tskIDLE_PRIORITY + 1,
        &xHandle
    );

    if (xReturned != pdPASS) {
        ESP_LOGD(LOG_TAG, "ERROR: xTaskCreate failed");
    }
}

void wsDeleteJsfileTask() {
    if(!xHandle) return;
    ESP_LOGD(LOG_TAG, "Delete old jsfile task");

    dukf_log_heap("Heap before delete task");

    lock_heap();

    vTaskDelete(xHandle);
    xHandle = NULL;

    dukf_log_heap("Heap after delete task");

    duktape_end();

    unlock_heap();

    dukf_log_heap("Heap after delete heap");
}

bool wsIsJsfileTaskRunning() {
    return !!xHandle;
}