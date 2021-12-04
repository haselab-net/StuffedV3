#include "Utils.h"
SemaphoreHandle_t createNonPriorityMutex(){
	SemaphoreHandle_t rv = xSemaphoreCreateBinary();
    xSemaphoreGive(rv);
    return rv;
}
void* shiftPointer(const void* p, int8_t offsetBytes) {
    return (void*)((char*)p + offsetBytes);
}
void pushPayload(void* &payload, const void* source, size_t byteSize) {
    memcpy(payload, source, byteSize);
    payload = shiftPointer(payload, byteSize);
}

size_t popPayloadStr(const void* &payload, const char* &target) {
    const char* p = (char*)payload;
    size_t len = 1;
    while (*p != '\0') {
        p++;
        len++;
    }
    target = (char*)payload;
    payload = shiftPointer(payload, len);
    return len;
}