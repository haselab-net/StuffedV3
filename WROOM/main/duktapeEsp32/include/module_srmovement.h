#ifndef MAIN_INCLUDE_MODULE_SRMOVEMENT_H_
#define MAIN_INCLUDE_MODULE_SRMOVEMENT_H_

#ifdef __cplusplus
#include "module_device.h"
#include "../../softRobot/Utils.h"
extern "C"{
#endif

#include <duktape.h>
#include "duktape_utils.h"
#include "esp_log.h"

duk_ret_t ModuleSRMovement(duk_context *ctx);

#ifdef __cplusplus
}

void onSrMovementReceiveCIUMovement(const void *movementData);
#endif

#endif /* MAIN_INCLUDE_MODULE_SRMOVEMENT_H_ */