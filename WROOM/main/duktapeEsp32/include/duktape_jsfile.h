#ifndef DUKTAPEESP32_DUKTAPE_JSFILE_H_
#define DUKTAPEESP32_DUKTAPE_JSFILE_H_

#include "duktape_event.h"

extern duk_context* esp32_duk_context;

void handle_event();

void duktape_start();

void duktape_end();

#endif