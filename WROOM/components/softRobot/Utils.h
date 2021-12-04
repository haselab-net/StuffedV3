#ifndef _SOFTROBOT_UTILS_H
#define _SOFTROBOT_UTILS_H
extern "C" {
    #include "CUtils.h"
}
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <freertos/semphr.h>

////////////////////////////////////////////////////////
//////////////////////// tool functions ////////////////
////////////////////////////////////////////////////////

//	non priority inherit mutex
SemaphoreHandle_t createNonPriorityMutex();

/////////////////////////////////// functions for pointers ////////////////////////////////
void* shiftPointer(const void* p, int8_t offsetBytes);
void pushPayload(void* &payload, const void* source, size_t byteSize);

template <class T>
void pushPayloadNum(void* &payload, const T &target) {
    pushPayload(payload, (void*)&target, sizeof(T));
}
template <class T>
void pushPayloadNumArray(void* &payload, const std::vector<T> &vec) {
    for (int i=0; i<vec.size(); i++) {
        pushPayloadNum(payload, vec[i]);
    }
}

template <class T>
void popPayloadNum(const void* &payload, T &target) {
    memcpy(&target, payload, sizeof(T));
    payload = shiftPointer(payload, sizeof(T));
}

size_t popPayloadStr(const void* &payload, const char* &target);

template <class T>
void popPayloadNumArray(const void* &payload, std::vector<T> &vec, size_t len) {
    vec.clear();
    vec.reserve(len);

    for (int i=0; i<len; i++) {
        T num;
        popPayloadNum(payload, num);
        vec.push_back(num);
    }
}

/////////////////////////////////// functions for duktape ////////////////////////////////
template <class T>
T saturateCast(T val, T min, T max) {
    if (val < min) return min;
    if (val > max) return max;
    return val;
}

#endif
