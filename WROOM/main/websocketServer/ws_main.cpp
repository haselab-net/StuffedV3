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
#include "WiFiEventHandler.h"

#include "ws_server.h"
#include "ws_wifi.h"
#include "ws_fs.h"

LOG_TAG("ws_main");

extern "C" void ws_main() {
    LOGD("Free heap at start: %d", esp_get_free_heap_size());

	// Boot the WiFi environment
	nvs_flash_init();
	tcpip_adapter_init();
    SRWiFi::wifi.init();

    // Mount the SPIFFS file system.
    #if defined(ESP_PLATFORM)
	    esp32_spiffs_mount();
    #endif /* ESP_PLATFORM */

    // start server
    createServer();
}
