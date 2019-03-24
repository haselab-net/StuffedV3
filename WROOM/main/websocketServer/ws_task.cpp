#include "ws_task.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "logging.h"
#include "duktape_jsfile.h"

static TaskHandle_t* xHandle = NULL;

extern void UdpCom_Lock();
extern void UdpCom_Unlock();

LOG_TAG("ws_task");

static void duktapeTask(void* pvParameters) {
    LOGD("Start running JSFile");

    duktape_start();

    LOGD("Finished running JSFile");

    while(1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
        printf("wait 1s\n");
    }
}

void wsCreateJsfileTask() {
    LOGD("Create new jsfile task");

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
    LOGD("Delete old jsfile task");

    UdpCom_Lock();
    
    vTaskDelete(xHandle);
    xHandle = NULL;

    duktape_end();

    UdpCom_Unlock();
}