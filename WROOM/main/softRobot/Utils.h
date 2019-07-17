#ifndef _SOFTROBOT_UTILS_H
#define _SOFTROBOT_UTILS_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <vector>

////////////////////////////////////////////////////////
//////////////////////// tool functions ////////////////
////////////////////////////////////////////////////////

/////////////////////////////////// functions for pointers ////////////////////////////////
void* shiftPointer(const void* p, int8_t offsetBytes);
void pushPayload(void* &payload, const void* source, size_t byteSize);

template <class T>
void popPayloadNum(const void* &payload, T &target) {
    memcpy(&target, payload, sizeof(T));
    payload = shiftPointer(payload, sizeof(T));
}

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

#endif