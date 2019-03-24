#include <freertos/FreeRTOS.h>
//#include <freertos/heap_regions.h>
#include <freertos/task.h>
#include <esp_event.h>
#include <esp_event_loop.h>
#include <esp_log.h>
#include <esp_system.h>
#include <esp_wifi.h>
#include <nvs_flash.h>

#include "logging.h"
#include "duktape_spiffs.h"
#include "WiFiEventHandler.h"

#include "ws_server.h"

LOG_TAG("ws_main");

/**
 * Mount & register virtual filesystem.
 */
void esp32_spiffs_mount() {
    esp_vfs_spiffs_conf_t conf = {
      .base_path = "/spiffs",
      .partition_label = NULL,
      .max_files = 5,
      .format_if_mount_failed = false
    };

    esp_err_t ret = esp_vfs_spiffs_register(&conf);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            LOGE("Failed to mount or format filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            LOGE("Failed to find SPIFFS partition");
        } else {
            LOGE("Failed to initialize SPIFFS (%d)", ret);
        }
        return;
    }

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(NULL, &total, &used);
    if (ret != ESP_OK) {
        LOGE("Failed to get SPIFFS partition information");
    } else {
        LOGI("Partition size: total: %d, used: %d", total, used);
    }

} // esp32_duktape_spiffs_mount

void init() {
    // Mount the SPIFFS file system.
    #if defined(ESP_PLATFORM)
	    esp32_spiffs_mount();
    #endif /* ESP_PLATFORM */

    createServer();
}

class SRWifiEventHandler: public WiFiEventHandler {
    esp_err_t staGotIp(system_event_sta_got_ip_t info) {
        //LOGD("GOT IP: %s", ip4addr_ntoa(info.ip_info.ip));
        return ESP_OK;
    }
};

static esp_err_t esp32_wifi_eventHandler(void *ctx, system_event_t *event) {
	return ESP_OK;
} // esp32_wifi_eventHandler

extern "C" void ws_main() {
    LOGD("Free heap at start: %d", esp_get_free_heap_size());

	// Boot the WiFi environment and once WiFi is ready, call init().
	nvs_flash_init();
	tcpip_adapter_init();
	ESP_ERROR_CHECK(esp_event_loop_init(esp32_wifi_eventHandler, NULL));
	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_wifi_init(&cfg));
	ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));

    init();
}