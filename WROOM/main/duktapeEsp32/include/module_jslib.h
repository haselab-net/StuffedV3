#ifndef MAIN_INCLUDE_MODULE_JSLIB_H_
#define MAIN_INCLUDE_MODULE_JSLIB_H_

#include <duktape.h>
duk_ret_t ModuleJSLib(duk_context *ctx);

void return_packet_to_jsfile(void* buffer, size_t buffer_size);

#endif /* MAIN_INCLUDE_MODULE_JSLIB_H_ */