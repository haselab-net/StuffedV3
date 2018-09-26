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
#include "../esptool_py/esptool/flasher_stub/rom_functions.h"  // "esptool_py/esptool/flasher_stub/rom_functions.h"
#include "TouchSensing.h"
#include "Motor.h"
#include "../../PIC/boardType.h"

int getch(){
    uint8_t data[1];
    int rv = uart_rx_one_char(data);
    if (rv == OK){
        return data[0];
    }else{
        return -1;
    }
}


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

    // Enable next line to clear all nvs enable. Use only when nvs makes trouble. 
#if 0
    nvs_flash_erase();
#endif

#if 1   //  pwm / adc test 
    static MotorDriver motor;
    motor.Init();
    motor.AdcRead();
    float pwm = -0.8f;
    while(1){
/*        int key = getch();
        if (key == 'p'){
            pwm = -pwm;
            printf("pwm = %f\r\n", pwm);
        }*/
        for(int i=0; i<3; ++i){
            motor.Pwm(i, pwm);
        }
        motor.AdcRead();
        printf("ADC:");
        for(int i=0; i<6; ++i){
            printf(" %d", motor.GetAdcRaw(i));
        }
        printf("\r\n");
    }
#endif

    uarts.Init();
    printf("Init uarts finished. ");
    printf("%d motors, %d force sensors found.\n", uarts.GetNTotalMotor(), uarts.GetNTotalForce());
	//wifiSmartConfig();
    //  init udp but not start
    udpCom.Init();
	printf("Init udp finished.\n");
    //  start wifi manager
    wifiMan();

    //  On old board, this prevents UARTs. 
#if 0    //defined BOARD2_COMBINATION
    touch_sensing.init();
    printf("Init Touch Sensing finished.\n");
#endif
    vTaskDelay(1000);
    udpCom.Start();
#if 0
    while(1){
        xEventGroupWaitBits(wifi_manager_event_group,
             WIFI_MANAGER_WIFI_CONNECTED_BIT, pdFALSE, pdFALSE, portMAX_DELAY);
             // WIFI_MANAGER_AP_STA_CONNECTED_BIT
        udpCom.Start();
        ESP_LOGI("udpCom", "Wifi Connected udpCom Start.\n");
        udpCom.Start();
        xEventGroupWaitBits(wifi_manager_event_group, WIFI_MANAGER_STA_DISCONNECT_BIT, pdFALSE, pdFALSE, portMAX_DELAY);
    }
#endif
}
