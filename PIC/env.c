#include "env.h"
#include <stdarg.h>

//int logLevel = LOG_LEVEL_ERROR;
int logLevel = LOG_LEVEL_INFO;




void vlogPrintf(int lv, const char* format, va_list va){
	if (lv >= logLevel){
	    vprintf(format, va);
	}
}
void logPrintfE(const char* format, ...){
	va_list va;
    va_start(va, format);
	vlogPrintf(LOG_LEVEL_ERROR, format, va);
	va_end(va);
}
void logPrintfW(const char* format, ...){
	va_list va;
    va_start(va, format);
	vlogPrintf(LOG_LEVEL_WARN, format, va);
	va_end(va);
}
void logPrintfI(const char* format, ...){
	va_list va;
    va_start(va, format);
	vlogPrintf(LOG_LEVEL_INFO, format, va);
	va_end(va);
}
