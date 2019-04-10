#ifndef DUKTAPEESP32_DUKTAPE_JSFILE_H_
#define DUKTAPEESP32_DUKTAPE_JSFILE_H_

#include "duktape_event.h"
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

extern duk_context* esp32_duk_context;
extern SemaphoreHandle_t esp32_duk_context_mutex;

void handle_event();

void duktape_start();

void duktape_end();

#endif