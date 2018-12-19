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
#include "esp_log.h"
#include "nvs_flash.h"
#include "wifiMan.h"
#include "wifiMan/http_server.h"
#include "wifiMan/wifi_manager.h"
#include "rom/uart.h"

#include "UdpCom.h"
#include "AllBoards.h"
#include "TouchSensing.h"
#include "MotorDriver.h"

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

#if 0    // Enable to clear all nvs enable. Use only when nvs makes trouble. 
    nvs_flash_erase();
#endif

#if 0   //  Code for debugging: pwm / adc test 
    motorDriver.Init();
    float pwm = -0.8f;
    int count = 0;
    while(1){
        int key = getch();
        if (key == 'p'){
            pwm = -pwm;
            printf("pwm = %f\r\n", pwm);
        }
        for(int i=0; i<3; ++i){
            motorDriver.Pwm(i, pwm);
        }
        if (count % 100 == 0){
            printf("ADC:");
            for(int i=0; i<6; ++i){
                printf(" %d", motorDriver.GetAdcVoltage(i));
            }
/*            printf(" Touch:");
            for(int i=0; i<touch.NPad(); ++i){
                printf(" %d", touch.Raw(i));
            }*/
            printf("\r\n");        
        }
        count ++;
    }
#endif
    
#if 0   //  touchPads can not work with JTAG debugger
    touchPads.Init();
#endif
    motorDriver.Init();
    allBoards.Init();
    printf("Init allBoards finished. ");
    printf("%d motors, %d force sensors found.\n", allBoards.GetNTotalMotor(), allBoards.GetNTotalForce());
	//wifiSmartConfig();
    //  init udp but not start
    udpCom.Init();
	printf("Init udp finished.\n");

    //  start wifi manager
    wifiMan();
    vTaskDelay(1000);
    
    //  start udp server.
    udpCom.Start();
#if 1   //  Code for debugging: show ADC values or motor angles.
    while(1){
#if 1   //  for raw ADC
        for(int i=0; i<6; ++i){
            int raw = motorDriver.GetAdcRaw(i);
            printf("%5d\t", raw);
        }
#else   //  for motor angle
        for(int i=0; i<3; ++i){
            printf("%d %2.2f   ", i, LDEC2DBL(motorState.pos[i]));
        }
#endif
        printf("\r\n");
        vTaskDelay(500);
    }
#endif

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
