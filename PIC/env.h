#ifndef ENV_H
#define ENV_H

//	Macro

//#define DEBUG
//#define MODULETEST    //  module test mode for debugging


#ifdef MODULETEST
#define DEBUG
#endif

extern int logLevel;
enum logLevelList{
	LOG_LEVEL_NONE,
	LOG_LEVEL_INFO,
	LOG_LEVEL_WARN,
	LOG_LEVEL_ERROR,	
};
#define LOGE	logPrintfE
#define LOGW	logPrintfW
#define LOGI	logPrintfI

void logPrintfE(const char* fmt,  ...);
void logPrintfW(const char* fmt,  ...);
void logPrintfI(const char* fmt,  ...);

#endif
