/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_task_wdt.h"
#include "UdpCom.h"
#include "UartCom.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "wifiMan.h"
#include "wifiMan/http_server.h"
#include "wifiMan/wifi_manager.h"
#include "TouchSensing.h"




extern "C" void app_main()
{        
    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
        chip_info.cores,
        (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
        (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");
    printf("silicon revision %d, ", chip_info.revision);
    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    //----------------------------------
    printf("!!! Stuffed Robot Start !!!\n");
    //  start wifi config tasks
    wifiMan();
	//wifiSmartConfig();
    uarts.Init();
    printf("Init uarts finished. ");
    printf("%d motors, %d force sensors found.\n", uarts.GetNTotalMotor(), uarts.GetNTotalForce());
    udpCom.Init();
	printf("Init udp finished.\n");
//  On old board, this prevents UARTs.
//    touch_sensing.init();
//    printf("Init Touch Sensing finished.\n");
    
    while(1){
        xEventGroupWaitBits(wifi_manager_event_group, WIFI_MANAGER_WIFI_CONNECTED_BIT, pdFALSE, pdFALSE, portMAX_DELAY);
        udpCom.Start();
        ESP_LOGI("udpCom", "Wifi Connected udpCom Start.\n");
        xEventGroupWaitBits(wifi_manager_event_group, WIFI_MANAGER_STA_DISCONNECT_BIT, pdFALSE, pdFALSE, portMAX_DELAY);
    }
}
