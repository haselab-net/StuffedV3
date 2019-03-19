#ifndef MAIN_INCLUDE_MODULE_JSFILE_H_
#define MAIN_INCLUDE_MODULE_JSFILE_H_

#include <duktape.h>
#include "duktape_utils.h"
#include "module_dukf.h"

duk_ret_t ModuleJSFile(duk_context *ctx);

void runFileTask(void* pvParameters);

#endif /* MAIN_INCLUDE_MODULE_JSFILE_H_ */