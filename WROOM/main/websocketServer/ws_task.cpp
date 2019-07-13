#include "ws_task.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "esp_log.h"
extern "C" {
#include "../duktapeEsp32/include/duktape_task.h"
#include "../duktapeEsp32/include/dukf_utils.h"
}
#include "../softRobot/UdpCom.h"

static char LOG_TAG[] = "ws_task";

void wsCreateJsfileTask() {
    if (!wsIsJsfileTaskRunning()){
        duktape_start();
    }
}

void wsDeleteJsfileTask() {
    if (wsIsJsfileTaskRunning()){
        duktape_end();
    }
}

bool wsIsJsfileTaskRunning() {
    return !! heap_context;
}
