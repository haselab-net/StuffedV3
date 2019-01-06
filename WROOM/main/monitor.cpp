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

#include "WroomEnv.h"
#include "UdpCom.h"
#include "AllBoards.h"
#include "TouchSensing.h"
#include "MotorDriver.h"
#include "monitor.h"
#include "UartForBoards.h"

Monitor Monitor::theMonitor;
int getch(){
    uint8_t ch;
    if (uart_read_bytes(UART_NUM_0, &ch, 1, 1) == 1){
        return ch;
    }
    return -1;
}
int getchWait(){
    uint8_t ch;
    uart_read_bytes(UART_NUM_0, &ch, 1, portMAX_DELAY);
    return ch;
}
void Monitor::AddCommand(MonitorCommandBase* c){
    commands.push_back(c);
}
void Monitor::ShowList(){
    for(int i=0; i<commands.size(); ++i){
        MonitorCommandBase* mc = commands[i];
        printf("%s\n", mc->Desc());
    }
}
void Monitor::Run(){
    uart_driver_install(UART_NUM_0, 1024, 1024, 10, NULL, 0);
    printf("Monitor start.\n");
    ShowList();
    while(1){
        uint8_t ch;
        uart_read_bytes(UART_NUM_0, &ch, 1, portMAX_DELAY);
        int i=0;
        for(; i<commands.size();++i){
            if (commands[i]->Desc()[0] == (char)ch){
                printf("%s\n", commands[i]->Desc());
                commands[i]->Func();
                break;
            }
        }
        if (i==commands.size()){
            ShowList();
        }
    }
}
MonitorCommandBase::MonitorCommandBase(){
    Monitor::theMonitor.AddCommand(this);
}
 
class MCEraseNvs: public MonitorCommandBase{
    const char* Desc(){ return "E Erase NVS flash"; }
    void Func(){
        printf("This command erase all NVS flash. Are you sure ? (Y/N)\n");
        while(1){
            int ch = getch();
            if (ch == 'y' || ch == 'Y'){
                nvs_flash_erase();
                printf("erased.\n");
                break;
            }else if(ch > 0){
                printf("canceled.\n");
                break;
            }
        }
    }
} mcEraseNvs;

class MCPwmTest: public MonitorCommandBase{
    const char* Desc(){ return "m Motor PWM Test"; }
    void Func(){
        const float delta = 0.1f;
        const char* up =   "qwertyu";
        const char* down = "asdfghj";
        float duty[MotorDriver::NMOTOR_DIRECT];
        motorDriver.bControl = false;
        for(int i=0; i<MotorDriver::NMOTOR_DIRECT; ++i){
            duty[i] = 0.0f;
        }
        printf("[ENTER/SPACE]:show state, [%s]:forward, [%s]:backword, other:quit\n" ,up, down);
        while(1){
            vTaskDelay(100);
            int ch = getch();
            if (ch == -1) continue;
            const char* f = NULL;
            if ( (f = strchr(up, ch)) ){
                int channel = f-up;
                if (channel < MotorDriver::NMOTOR_DIRECT){
                    duty[channel] += delta;
                    if (duty[channel] > 1.0f) duty[channel] = 1.0f;
                }
            }else if ( (f = strchr(down, ch)) ) {
                int channel = f-down;
                if (channel < MotorDriver::NMOTOR_DIRECT){
                    duty[channel] -= delta;
                    if (duty[channel] < -1.0f) duty[channel] = -1.0f;
                }
            }else if (ch == '\r' || ch == ' '){
                printf("PWM duty = ");
                for(int i=0; i<MotorDriver::NMOTOR_DIRECT; ++i){
                    printf("  %8.1f", duty[i]);
                }
                printf("   Angle =");
                for(int i=0; i<MotorDriver::NMOTOR_DIRECT; ++i){
                    printf("  %8.2f", LDEC2DBL(motorState.pos[i]));
                }
                printf("\n");
            }else{
                break;
            }
            for(int i=0; i<MotorDriver::NMOTOR_DIRECT; ++i){
                motorDriver.Pwm(i, duty[i]);
            }
        }
        motorDriver.bControl = true;
    }
} mcPwmTest;

class MCShowADC: public MonitorCommandBase{
    const char* Desc(){ return "a Show ADC and motor angles"; }
    void Func(){
        while(1){
            for(int i=0; i<MotorDriver::NMOTOR_DIRECT*2; ++i){
                int raw = motorDriver.GetAdcRaw(i);
                printf("%5d\t", raw);
            }
            for(int i=0; i<MotorDriver::NMOTOR_DIRECT; ++i){
                printf("\t%4.2f", LDEC2DBL(motorState.pos[i]));
            }
            printf("\n");
            vTaskDelay(200);
            if (getch() >= 0) break;
        }
    }
} mcShowADC;

class MCShowTouch: public MonitorCommandBase{
    const char* Desc(){ return "t Show Touch sensors"; }
    void Func(){
        while(1){
            for(int i=0; i<touchPads.NPad(); ++i){
                printf("%d\t", touchPads.Raw(i));
            }
            printf("\n");
            vTaskDelay(200);
            if (getch() >= 0) break;
        }
    }
} mcShowTouch;

class MCWriteCmd: public MonitorCommandBase{
    const char* Desc(){ return "w Write command to UART"; }
    void Func(){
        UdpCmdPacket* recv = &udpCom.recvs.Poke();
        recv->command = CI_DIRECT;
        recv->length = recv->CommandLen();
        recv->count = udpCom.commandCount + 1;
        udpCom.recvs.Write();
        #if !UDP_UART_ASYNC
        xTaskNotifyGive(udpCom.taskExeCmd);
        #endif
    }
} mcWriteCmd;


struct DebugFlag{
    bool* flag;
    const char* msg;
};
static struct DebugFlag flags[] = {
    {&UartForBoards::bDebug, "u UartForBoards"},
};
class MCDebugFlag: public MonitorCommandBase{
    const char* Desc(){ return "d change debug flags"; }
    void Func(){
        while(1){
            for(int i=0; i<sizeof(flags)/sizeof(flags[0]); ++i){
                printf ("%s = %s\n", flags[i].msg, *flags[i].flag ? "true" : "false");
            }
            int ch = getchWait();
            int i=0;
            for(; i<sizeof(flags)/sizeof(flags[0]); ++i){
                if (flags[i].msg[0] == ch){
                    *flags[i].flag = !*flags[i].flag;
                    break;
                }
            }
            if (i == sizeof(flags)/sizeof(flags[0])) break;
        }
    }
} mcDebugFlag;


void monitor(){
    Monitor::theMonitor.Run();    
}