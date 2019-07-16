#include "Utils.h"

void* shiftPointer(void* p, int8_t offsetBytes) {
    return (void*)((char*)p + offsetBytes);
}
void pushPayload(void* &payload, void* source, size_t byteSize) {
    memcpy(payload, source, byteSize);
    payload = shiftPointer(payload, byteSize);
}