#ifndef MAIN_INCLUDE_MODULE_IFTTT_H_
#define MAIN_INCLUDE_MODULE_IFTTT_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <duktape.h>
#include "duktape_utils.h"

#include "mqtt_client.h"

duk_ret_t ModuleIoT(duk_context *ctx);

void iotBeforeStopJSTask();

#ifdef __cplusplus
}
#endif

#endif /* MAIN_INCLUDE_MODULE_IFTTT_H_ */