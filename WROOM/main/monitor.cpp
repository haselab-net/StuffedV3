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
#include "driver/uart.h"

#include "UdpCom.h"
#include "AllBoards.h"
#include "TouchSensing.h"
#include "MotorDriver.h"
#include "monitor.h"

Monitor Monitor::theMonitor;
int getch(){
    uint8_t ch;
    if (uart_read_bytes(UART_NUM_0, &ch, 1, 1) == 1){
        return ch;
    }
    return -1;
}
void Monitor::AddCommand(MonitorCommandBase* c){
    commands.push_back(c);
}
void Monitor::Run(){
    uart_driver_install(UART_NUM_0, 1024, 1024, 10, NULL, 0);
    printf("Monitor start.\n");
    while(1){
        uint8_t ch;
        uart_read_bytes(UART_NUM_0, &ch, 1, portMAX_DELAY);
        int i=0;
        for(; i<commands.size();++i){
            if (commands[i]->Desc()[0] == (char)ch){
                printf("%s\n", mc->Desc());
                commands[i]->Func();
                break;
            }
        }
        if (i==commands.size()){
            for(int i=0; i<commands.size(); ++i){
                MonitorCommandBase* mc = commands[i];
                printf("%s\n", mc->Desc());
            }
        }
    }
}
MonitorCommandBase::MonitorCommandBase(){
    Monitor::theMonitor.AddCommand(this);
}
 
class MCShowADC: public MonitorCommandBase{
    const char* Desc(){ return "a Show ADC and motor angles"; }
    void Func(){
        while(1){
            for(int i=0; i<6; ++i){
                int raw = motorDriver.GetAdcRaw(i);
                printf("%5d\t", raw);
            }
            for(int i=0; i<3; ++i){
                printf("\t%4.2f", LDEC2DBL(motorState.pos[i]));
            }
            printf("\n");
            vTaskDelay(200);
            if (getch() >= 0) break;
        }
    }
} mcShowADC;

void monitor(){
    Monitor::theMonitor.Run();    
}