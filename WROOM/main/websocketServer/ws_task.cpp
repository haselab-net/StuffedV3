#include "ws_task.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "esp_log.h"
extern "C" {
    #include "duktape_jsfile.h"
}
#include "UdpCom.h"

static TaskHandle_t xHandle = NULL;

static char LOG_TAG[] = "ws_task";

static void duktapeTask(void* pvParameters) {
    ESP_LOGD(LOG_TAG, "Start running JSFile");

    duktape_start();

    ESP_LOGD(LOG_TAG, "Finished running JSFile");

    while(1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
        printf("wait 1s\n");
    }
}

void wsCreateJsfileTask() {
    ESP_LOGD(LOG_TAG, "Create new jsfile task");

    BaseType_t xReturned = xTaskCreate(
        duktapeTask,
        "duktape_task",
        16*1024,
        NULL,
        tskIDLE_PRIORITY+1,
        &xHandle
    );

    if (xReturned != pdPASS) {
        ESP_LOGD(LOG_TAG, "ERROR: xTaskCreate failed");
    }
}

void wsDeleteJsfileTask() {
    if(xHandle==NULL) return;
    ESP_LOGD(LOG_TAG, "Delete old jsfile task");

    vTaskDelete(xHandle);
    xHandle = NULL;

    duktape_end();
}

bool wsIsJsfileTaskRunning() {
    return !!xHandle;
}