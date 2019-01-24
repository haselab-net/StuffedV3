/*
  Tiny sprintf module
   for Embedded microcontrollers

   (Ver 1.0)
*/

#ifndef _TSPRINTF_H_
#define _TSPRINTF_H_

#include <stdarg.h>

#ifdef __cplusplus
extern "C"{
#endif

extern int tsprintf(const char* ,char* , ...);
extern int vtsprintf(char* buff,const char* fmt,va_list arg);

#ifdef __cplusplus
}
#endif

#endif /* _TSPRINTF_H_ */
