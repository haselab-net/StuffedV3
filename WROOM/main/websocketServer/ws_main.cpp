#include <freertos/FreeRTOS.h>
//#include <freertos/heap_regions.h>
#include <freertos/task.h>
#include <esp_event.h>
#include <esp_event_loop.h>
#include <esp_log.h>
#include <esp_system.h>
#include <esp_wifi.h>
#include <nvs_flash.h>

#include "ws_server.h"
#include "WiFiEventHandler.h"

static const char* LOG_TAG = "ws_main";

void init() {
    createWsServer();
}

class MyWifiEventHandler: public WiFiEventHandler {
    esp_err_t staGotIp(system_event_sta_got_ip_t info) {
        ESP_LOGD(LOG_TAG, "GOT IP: %s", ip4addr_ntoa(info.ip_info.ip));
        return ESP_OK;
    }
};
extern "C" void ws_main() {
    ESP_LOGD(LOG_TAG, "Free heap at start: %d", esp_get_free_heap_size());

	// Boot the WiFi environment and once WiFi is ready, call init().
	nvs_flash_init();
	tcpip_adapter_init();
	ESP_ERROR_CHECK(esp_event_loop_init(esp32_wifi_eventHandler, NULL));
	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_wifi_init(&cfg));
	ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));

    init();
}