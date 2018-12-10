#ifndef ENV_H
#define ENV_H

/**	env.h
 * This file defines build enviroment and purpose related thigns.
 * For board type selection, please refer "boardType.h"
 */

//-----------------------------------------------------------
//	Macro
//#define DEBUG
//#define MODULETEST    //  module test mode for debugging

#ifdef __XC32
#define PIC	1
#elif defined __xtensa__
#define WROOM	1
#else
#error processor macro is undefined.
#endif

#ifdef WROOM
typedef unsigned int uint32_t;
#define DISABLE_INTERRUPT
#define ENABLE_INTERRUPT
#endif

#ifdef PIC
#define DISABLE_INTERRUPT 	asm volatile("di"); // Disable all interrupts  
#define ENABLE_INTERRUPT	asm volatile("ei"); // Enable all interrupt	
#endif



#ifdef MODULETEST
#define DEBUG
#endif

//-----------------------------------------------------------
//	Log
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
