#include "duktape.h"
#include "../lowmemSupport.h"
#include "soc/soc_memory_layout.h"
#include <assert.h>

#if 0
#define HEAPADDR	0x3FFB0000
void* heap_ptr_dec16(void* udata, duk_uint16_t x){
	void* rv = (void*)(x ? HEAPADDR + (x << 2) : 0);
	printf("DEC %x -> %x\n", (int)x, (int)rv);
	return rv;
}
duk_uint16_t heap_ptr_enc16(void* udata, void* x){
	uint16_t rv = x ? (duk_uint16_t)((duk_uint32_t)x - HEAPADDR) >> 2 : 0;
	printf("ENC %x -> %x\n", (int)x, (int)rv);
	assert((uint32_t)x % 4 == 0);
	assert(x == NULL || (HEAPADDR < (uint32_t)x && (uint32_t)x < HEAPADDR+0x10000*4));
	return rv;
}
#endif

//#define LMS_SHOWALLOC
#if 0
#define LMS_SHOWLARGE
char* loadedStr[NLOADEDSTR];
const duk_uint8_t* extstr_intern_check(void* udata, void* str, duk_size_t blen){
	int i;
	if (blen < 80) return NULL;
#ifdef LMS_SHOWALLOC
	printf("JS: extstr_intern_check for 0x%x len %d ---------------------'\n", (unsigned int)str, blen);
	fwrite(str, blen > 200 ? 200 : blen, 1, stdout);
	printf("\n-------------------------------------------------------\nCheck ");
#endif
	for(i=0; i<NLOADEDSTR && loadedStr[i]; ++i){
#ifdef LMS_SHOWALLOC
		printf(" %d(0x%x)", i, (unsigned int)loadedStr[i]);
#endif
		//fwrite(loadedStr[i], blen > 30 ? 30 : blen, 1, stdout);
		//printf("\n");
		if (loadedStr[i] == str){
			int len = strlen(loadedStr[i]);
			if (blen != len){
				printf("ERROR in lowmemSupport.c: loadStr's len %d != blen %d\n", len, blen);
				return NULL;
			}
#ifdef LMS_SHOWALLOC
			printf(" hit.\n");
#endif
			return (duk_uint8_t*)loadedStr[i];
		}
	}
#ifdef LMS_SHOWALLOC
	printf("NOT found !!!\n");
#endif
#ifdef LMS_SHOWLARGE
	const int limit = 200;
	const int show = 160;
	if (blen >= limit){
		printf("JS: %d bytes at 0x%x will use heap ---------------------'\n", blen, (unsigned int)str);
		fwrite(str, blen > show ? show : blen, 1, stdout);
		printf("\n-------------------------------------------------------\n");
	}
#endif
	return NULL;
}
#else

//#define LMS_SHOWALLOC
#define LMS_SHOWLARGE
const duk_uint8_t* extstr_intern_check(void* udata, void* str, duk_size_t blen){
	if (blen < 80) return NULL;
#ifdef LMS_SHOWALLOC
	printf("JS: extstr_intern_check for 0x%x len %d ---------------------'\n", (unsigned int)str, blen);
	fwrite(str, blen > 200 ? 200 : blen, 1, stdout);
	printf("\n-------------------------------------------------------\nCheck ");
#endif
	if (!esp_ptr_byte_accessible(str) && !esp_ptr_external_ram(str)){
		//	if not in ram, it is rom string and can use directly.
		int len = strlen(str);
		if (len == blen){
			return str;
		}else{
			printf("ERROR in lowmemSupport.c: strlen(str) %d != blen %d\n", len, blen);
		}
	}
#ifdef LMS_SHOWLARGE
	const int limit = 200;
	const int show = 160;
	if (blen >= limit){
		printf("JS: %d bytes at 0x%x will use heap ---------------------'\n", blen, (unsigned int)str);
		fwrite(str, blen > show ? show : blen, 1, stdout);
		printf("\n-------------------------------------------------------\n");
	}
#endif
	return NULL;
}
#endif

void extstr_free(void* udata, const void* str){
}
