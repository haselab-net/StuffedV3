#pragma once
#ifdef __cplusplus
extern "C" {
#endif
	typedef enum {
		ESP_LOG_NONE,       /*!< No log output */
		ESP_LOG_ERROR,      /*!< Critical errors, software module can not recover on its own */
		ESP_LOG_WARN,       /*!< Error conditions from which recovery measures have been taken */
		ESP_LOG_INFO,       /*!< Information messages which describe normal flow of events */
		ESP_LOG_DEBUG,      /*!< Extra information which is not necessary for normal use (values, pointers, sizes, etc). */
		ESP_LOG_VERBOSE     /*!< Bigger chunks of debugging information, or frequent messages which can potentially flood the output. */
	} esp_log_level_t;
	void ESP_LOGD(const char* tag, const char* fmt, ...);
	void ESP_LOGV(const char* tag, const char* fmt, ...);
	void ESP_LOGI(const char* tag, const char* fmt, ...);
	void ESP_LOGW(const char* tag, const char* fmt, ...);
	void ESP_LOGE(const char* tag, const char* fmt, ...);
#define ESP_ERROR_CHECK(x)
#ifdef __cplusplus
}
#endif