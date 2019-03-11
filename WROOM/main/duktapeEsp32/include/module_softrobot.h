#ifndef MAIN_INCLUDE_MODULE_SOFTROBOT_H_
#define MAIN_INCLUDE_MODULE_SOFTROBOT_H_

#include <duktape.h>
duk_ret_t ModuleSoftrobot(duk_context *ctx);

void return_packet(duk_context* ctx, void* buffer, size_t buffer_size);

#endif /* MAIN_INCLUDE_MODULE_SOFTROBOT_H_ */