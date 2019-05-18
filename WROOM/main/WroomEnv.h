#pragma once
#include "../../PIC/env.h"

#define USE_DUKTAPE true        //  use Duktape or WifiMan 

#ifdef __cplusplus
extern "C"{
#endif

void log_level_set(const char* t, int level);
void log_tag_desc(const char* t, const char* desc);

#ifdef __cplusplus
}
#endif
