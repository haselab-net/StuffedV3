#ifdef __cplusplus
extern "C" {
#endif
	void ESP_LOGI(const char* tag, const char* fmt, ...);
	void ESP_LOGW(const char* tag, const char* fmt, ...);
	void ESP_LOGE(const char* tag, const char* fmt, ...);
#define ESP_ERROR_CHECK(x)
#ifdef __cplusplus
}
#endif