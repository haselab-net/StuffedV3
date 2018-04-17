#ifndef ARRAYRING_H
#define ARRAYRING_H
#include <stdio.h>

template <class T, int N>
class ArrayRing {
	T buf[N];
	int read, write;
public:
	const int bufLen = N;
	T& operator [] (size_t index) { return buf[index]; }
	void Clear(){
		write = read;
	}
	T& Peek() {
		return buf[read];
	}
	T& Read(){
		T& rv = buf[read];
		read = (read+1) % N;
		return rv;
	}
	T& Poke() {
		return buf[write];
	}
	T& Write() {
		T& rv = buf[write];
		write = (write+1) % N;
		return rv;
	}
	int WriteAvail() {
		int rv = read - write;
		if (rv <= 0) rv += N;
		return rv;
	}
	int ReadAvail() {
		int rv = write - read;
		if (rv < 0) rv += N;
		return rv;
	}
};


#endif
