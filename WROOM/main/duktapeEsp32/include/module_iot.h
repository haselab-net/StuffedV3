#ifndef MAIN_INCLUDE_MODULE_IFTTT_H_
#define MAIN_INCLUDE_MODULE_IFTTT_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <duktape.h>
#include "duktape_utils.h"

duk_ret_t ModuleIoT(duk_context *ctx);

#ifdef __cplusplus
}
#endif

extern bool isTCPWaiting;

void stopWaitingEventTask();

#endif /* MAIN_INCLUDE_MODULE_IFTTT_H_ */