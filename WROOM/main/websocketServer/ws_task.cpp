#include "ws_task.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "esp_log.h"
extern "C" {
#include "../duktapeEsp32/include/duktape_task.h"
#include "../duktapeEsp32/include/dukf_utils.h"
}
#include "../softRobot/UdpCom.h"

#include "ws_ws.h"

static char LOG_TAG[] = "ws_task";

void wsCreateJsfileTask() {
    if (!wsIsJsfileTaskRunning()){
        duktape_start();
    }

    switchOfflineModeSuccess();
}

static void callDuktapeEnd(void* arg){
    TaskHandle_t* task = (TaskHandle_t*)arg;
    TaskHandle_t t = *task;
    free(task);
    duktape_end();

    ESP_LOGI(LOG_TAG, "jsfile task deleted");
    switchOfflineModeSuccess();

    vTaskDelete(t);
}

void wsDeleteJsfileTask() {
    if (wsIsJsfileTaskRunning()){
        TaskHandle_t* task = (TaskHandle_t*)malloc(sizeof(TaskHandle_t));
        xTaskCreate(callDuktapeEnd, "dukEnd", 1024*4, task, tskIDLE_PRIORITY+1, task);
    } else {
        switchOfflineModeSuccess();
    }
}

bool wsIsJsfileTaskRunning() {
    return !! heap_context;
}
