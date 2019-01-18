#include "env.h"
#include <stdarg.h>

//int logLevel = LOG_LEVEL_ERROR;
int logLevel = LOG_LEVEL_INFO;    //  too heavy for real usage.


#ifdef _WIN32
extern void logVprintf(const char* format, va_list va);
void vlogPrintf(int lv, const char* format, va_list va) {
	if (lv >= logLevel) {
		logVprintf(format, va);
	}
}
#else
void vlogPrintf(int lv, const char* format, va_list va){
	if (lv >= logLevel){
	    vprintf(format, va);
	}
}
#endif

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
