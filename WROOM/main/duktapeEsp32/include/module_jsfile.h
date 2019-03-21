#ifndef MAIN_INCLUDE_MODULE_JSFILE_H_
#define MAIN_INCLUDE_MODULE_JSFILE_H_

duk_ret_t ModuleJSFile(duk_context *ctx);

void runFileTask(void* pvParameters);
void test(void* pvParameters);
void createJSFileHeap();

void jsfile_exec_packet_callback(void* buffer, size_t buffer_size);

#endif /* MAIN_INCLUDE_MODULE_JSFILE_H_ */