#ifndef ARRAYRING_H
#define ARRAYRING_H
#include <stdio.h>

template <class T, int N>
class ArrayRing {
protected:
	T buf[N];
	volatile int read, write;
public:
	const int bufLen = N;
	T& operator [] (size_t index) { return buf[index]; }
	void Clear(){
		write = read;
	}
	T& Peek() {
		return buf[read];
	}
	void Read(){
		read = (read+1) % N;
	}
	T& Poke() {
		return buf[write];
	}
	void Write() {
		write = (write+1) % N;
	}
	int WriteAvail() {
		/*	old code 2021.12.3
		int rv = read - write;
		if (rv <= 0) rv += N;
		return rv;	*/
		int rv = read - write - 1;
		if (rv < 0) rv += N;
		return rv;
	}
	int ReadAvail() {
		int rv = write - read;
		if (rv < 0) rv += N;
		return rv;
	}
};


#endif
