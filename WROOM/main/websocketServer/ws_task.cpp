#include "ws_task.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "esp_log.h"
extern "C" {
    #include "duktape_jsfile.h"
}
#include "UdpCom.h"

static TaskHandle_t* xHandle = NULL;

extern void UdpCom_Lock();
extern void UdpCom_Unlock();

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

    xTaskCreate(
        duktapeTask,
        "duktape_task",
        16*1024,
        NULL,
        tskIDLE_PRIORITY+1,
        xHandle
    );
}

void wsDeleteJsfileTask() {
    if(!xHandle) return;
    ESP_LOGD(LOG_TAG, "Delete old jsfile task");

    UdpCom_Lock();
    
    vTaskDelete(xHandle);
    xHandle = NULL;

    duktape_end();

    UdpCom_Unlock();
}