#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#ifndef _WIN32
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_task_wdt.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "rom/uart.h"
#endif

#include "UdpCom.h"
#include "AllBoards.h"
#include "TouchSensing.h"
#include "MotorDriver.h"
#include "monitor.h"

extern "C" void softRobot_main()    //  called from app_main in main.cpp 
{        
    //----------------------------------
    logPrintf("!!! Stuffed Robot Start !!!\n");   
	//nvs_flash_erase();

    motorDriver.Init();
#if 1   //  touchPads can not work with JTAG debugger
    touchPads.Init();
#endif
    allBoards.Init();
    logPrintf("Init allBoards finished. ");
    logPrintf("%d motors, %d current sensors, %d force sensors found.\n", allBoards.GetNTotalMotor(), allBoards.GetNTotalCurrent(), allBoards.GetNTotalForce());

    udpCom.Init();    //  init command processing for udp.
    udpCom.Start();   //  start UDP server.
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
    //  monitor start
    monitor();
}
