#include "Utils.h"

void* shiftPointer(const void* p, int8_t offsetBytes) {
    return (void*)((char*)p + offsetBytes);
}
void pushPayload(void* &payload, const void* source, size_t byteSize) {
    memcpy(payload, source, byteSize);
    payload = shiftPointer(payload, byteSize);
}