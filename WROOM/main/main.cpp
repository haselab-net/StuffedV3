#include "WroomEnv.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#ifndef _WIN32
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_task_wdt.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "rom/uart.h"
#include "ws_task.h"
#endif
#include "monitor.h"
#include "ws_fs.h"

static const char* TAG="main";

extern "C" void softRobot_main();
#if defined USE_DUKTAPE && !defined _WIN32
extern "C" void duktape_main();
extern "C" void ws_main();
#endif

#if CONFIG_HEAP_TRACING
#include "esp_heap_trace.h"
#define NUM_RECORDS 40
static heap_trace_record_t trace_record[NUM_RECORDS]; // This buffer must be in internal RAM
#endif

extern "C" void app_main(){
#ifndef _WIN32
	esp_log_level_set("*", ESP_LOG_INFO);
    {
        esp_chip_info_t chip_info;
        esp_chip_info(&chip_info);
        printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");
        printf("silicon revision %d, ", chip_info.revision);
        printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
                (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
        esp_log_level_set("*", ESP_LOG_INFO);
        ESP_LOGI(TAG, "Initial heap size: %d \n", esp_get_free_heap_size());
    }
    #if CONFIG_HEAP_TRACING
    ESP_ERROR_CHECK( heap_trace_init_standalone(trace_record, NUM_RECORDS) );
    #endif
#endif 
#if 1
    softRobot_main();
	ESP_LOGI(TAG, "after softRobot_main heap size: %d \n", esp_get_free_heap_size());
#endif

#if defined USE_DUKTAPE && ! defined _WIN32
    esp_log_level_set("*", ESP_LOG_DEBUG);
    esp_log_level_set("clk", ESP_LOG_INFO);
    esp_log_level_set("CPPNVS", ESP_LOG_INFO);
    esp_log_level_set("cpu_start", ESP_LOG_INFO);
    esp_log_level_set("esp_dbg_stubs", ESP_LOG_INFO);
    esp_log_level_set("event", ESP_LOG_INFO);
    esp_log_level_set("heap_init", ESP_LOG_INFO);
    esp_log_level_set("HttpServer", ESP_LOG_INFO);
    esp_log_level_set("HttpServerTask", ESP_LOG_INFO);
    esp_log_level_set("intr_alloc", ESP_LOG_INFO);
    esp_log_level_set("main", ESP_LOG_INFO);
    esp_log_level_set("nvs", ESP_LOG_INFO);
    esp_log_level_set("phy", ESP_LOG_INFO);
    esp_log_level_set("phy_init", ESP_LOG_INFO);
    esp_log_level_set("pthread", ESP_LOG_INFO);
    esp_log_level_set("RTC_MODULE", ESP_LOG_INFO);
    esp_log_level_set("Socket", ESP_LOG_INFO);
    esp_log_level_set("system_api", ESP_LOG_INFO);
    esp_log_level_set("Task", ESP_LOG_INFO);
    esp_log_level_set("tcpip_adapter", ESP_LOG_INFO);
    esp_log_level_set("WiFi", ESP_LOG_INFO);
    esp_log_level_set("WiFiEventHandler", ESP_LOG_INFO);
    esp_log_level_set("ws_fs", ESP_LOG_INFO);
    esp_log_level_set("ws_main", ESP_LOG_INFO);
    esp_log_level_set("ws_wifi", ESP_LOG_INFO);
	
    ws_main();
    ESP_LOGI(TAG, "after ws_main heap size: %d \n", esp_get_free_heap_size());
#if 1
	if(!wsIsJsfileTaskRunning()) {
        combineMainFiles();
        wsCreateJsfileTask();
        ESP_LOGI(TAG ,"Start running default jsfile task");
    }
#endif
#endif
    Monitor::theMonitor.Init();
    Monitor::theMonitor.Run();  //  monitor start. never return;
}
