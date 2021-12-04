#include "CUtils.h"
SemaphoreHandle_t createNonPriorityMutex(){
	SemaphoreHandle_t rv = xSemaphoreCreateBinary();
    xSemaphoreGive(rv);
    return rv;
}
