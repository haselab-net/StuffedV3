#ifndef MAIN_INCLUDE_MODULE_SRCOMMAND_H_
#define MAIN_INCLUDE_MODULE_SRCOMMAND_H_

#include <duktape.h>

void commandMessageHandler(void* buffer, size_t buffer_size);

duk_ret_t ModuleSRCommand(duk_context *ctx);

#endif /* MAIN_INCLUDE_MODULE_SRCOMMAND_H_ */