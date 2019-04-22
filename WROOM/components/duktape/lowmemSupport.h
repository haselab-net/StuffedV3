const duk_uint8_t* extstr_intern_check(void* udata, void* str, duk_size_t blen);
void extstr_free(void* udata, const void* str);

#if 0
struct duk_hthread;
typedef struct duk_hthread duk_hthread;
void duk__concat_and_join_helper(duk_hthread *thr, duk_idx_t count_in, duk_bool_t is_join);
#define NLOADEDSTR	10
extern char* loadedStr[NLOADEDSTR];
#endif

#if 0
void* heap_ptr_dec16(void* udata, duk_uint16_t x);
duk_uint16_t heap_ptr_enc16(void* udata, void* x);
#endif
#if 0
inline void* heap_ptr_dec16(void* udata, duk_uint16_t x){
	return (void*)(x ? 0x3FFC0000 + (x << 2) : 0);
}
inline duk_uint16_t heap_ptr_enc16(void* udata, void* x){
	return x ? (duk_uint16_t)((duk_uint32_t)x - 0x3FFC0000) >> 2 : 0;
}
inline const duk_uint8_t* extstr_intern_check(void* udata, void* str, duk_size_t blen){
	return NULL;
}
inline void extstr_free(void* udata, const void* str){
}
#endif
