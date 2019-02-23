#include <freertos/FreeRTOS.h>
//#include <freertos/heap_regions.h>
#include <freertos/task.h>
#include <esp_event.h>
#include <esp_event_loop.h>
#include <esp_log.h>
#include <esp_system.h>
#include <esp_wifi.h>
//#include <heap_alloc_caps.h>

extern "C" void softRobot_main();
extern "C" void duktape_main();

extern "C" void app_main(){
	esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    LOGD("This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
        chip_info.cores,
        (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
        (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");
    LOGD("silicon revision %d, ", chip_info.revision);
    LOGD("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
	
	duktape_main();
	softRobot_main();
}
