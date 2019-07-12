#include <stdio.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/event_groups.h>
#ifndef _WIN32
#include <logging.h>
#include <esp_system.h>
#include <esp_spi_flash.h>
#include <esp_task_wdt.h>
#include <nvs_flash.h>
#include <rom/uart.h>
#endif

#include "UdpCom.h"
#include "AllBoards.h"
#include "TouchSensing.h"
#include "MotorDriver.h"
#include "Movement.h"
#ifndef USE_DUKTAPE
#include "../wifiMan/wifiMan.h"
#endif
LOG_TAG("sr_main");

extern "C" void softRobot_main()    //  called from app_main in main.cpp 
{        
    //  Search sub boards.
    LOGI("Soft Robot Starts. Search sub boards.");
    allBoards.Init();
    LOGI("%d motors, %d current sensors, %d force sensors and %d touch pads found.", 
        allBoards.GetNTotalMotor(), allBoards.GetNTotalCurrent(), allBoards.GetNTotalForce(), allBoards.GetNTotalTouch());
    //  Init MCPWM and ADC
    motorDriver.Init();
#if 1   //  touchPads can not work with JTAG debugger
    touchPads.Init();
    LOGD("nPads %d", touchPads.NPad());
#endif

    initMovementDS();

#ifdef USE_DUKTAPE
    udpCom.Init();    //  init command processing for udp.
#else
    wifiMan();        //  Start wifi manager. 
    udpCom.Init();    //  init command processing for udp.
#endif
}
