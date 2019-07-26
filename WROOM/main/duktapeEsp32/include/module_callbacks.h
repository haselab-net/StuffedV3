#ifndef MAIN_INCLUDE_MODULE_CALLBACKS_H_
#define MAIN_INCLUDE_MODULE_CALLBACKS_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <duktape.h>
#include "duktape_utils.h"
#include "duktape_event.h"

duk_ret_t ModuleCallbacks(duk_context *ctx);

void callbacksBeforeStopJSTask();

#ifdef __cplusplus
}

#include <vector>
using namespace std;
void onRcvTouchMessage(const vector<int16_t> &oldTouch, const vector<int16_t> &newTouch);
#endif

#endif /* MAIN_INCLUDE_MODULE_CALLBACKS_H_ */