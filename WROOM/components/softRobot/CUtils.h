#ifndef _SOFTROBOT_CUTILS_H
#define _SOFTROBOT_CUTILS_H
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
//	non priority inherit mutex
SemaphoreHandle_t createNonPriorityMutex();

#endif
