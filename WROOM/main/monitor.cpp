#include <stdio.h>
#include <string.h>
#include <sstream>
#include <fstream>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#ifndef _WIN32
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_task_wdt.h"
#include "esp_heap_trace.h"
#include "nvs_flash.h"
#include "rom/uart.h"
#endif
#include "esp_log.h"
#include "driver/uart.h"

#include "../WroomEnv.h"
#include "SoftRobot/UdpCom.h"
#include "SoftRobot/AllBoards.h"
#include "SoftRobot/TouchSensing.h"
#include "SoftRobot/MotorDriver.h"
#include "monitor.h"
#include "SoftRobot/UartForBoards.h"
extern "C" {
#include "duktapeEsp32/include/module_jslib.h"
#include "duktapeEsp32/include/duktape_jsfile.h"
}
#include "duktapeEsp32/include/module_srcommand.h"

#include "websocketServer/ws_command.h"
#include "websocketServer/ws_task.h"
#include "websocketServer/ws_fs.h"
#include "espfs.h"
#include "espfsStream.h"

#include "../duktapeEsp32/include/logging.h"
LOG_TAG("Monitor");


Monitor Monitor::theMonitor;

const char* MonitorCommandBase::Tag(){
    return "Mon"; 
}

#ifndef _WIN32
int getchNoWait(){
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
#else
#include <conio.h>
int getchNoWait() {
	if (_kbhit()) return _getch();
	return -1;
}
int getchWait() {
	while (1) {
		if (_kbhit()) {
			return _getch();
		}
		vTaskDelay(20);
	}
}
#endif

static void getLine(char* buf, int len){
    int cur = 0;
    while(1){
        fflush(stdout);
        int ch = getchWait();
        switch (ch){
        case '\b':
            if (cur > 0) cur--;
            conPrintf("\b \b");
            break;
        case '\r':
            buf[cur] = '\0';
            conPrintf("\n");
            return;
            break;
        default:
            buf[cur] = ch;
            if (cur < len) cur ++;
            conPrintf("%c", (char)ch);
            break;
        }
    }
}

void Monitor::AddCommand(MonitorCommandBase* c){
    commands.push_back(c);
}
void Monitor::ShowList(){
	conPrintf("Top level commands:\n");
	for(int i=0; i<(int)commands.size(); ++i){
        MonitorCommandBase* mc = commands[i];
        conPrintf(" %s\n", mc->Desc());
    }
}
void Monitor::Init(){
    uart_driver_install(UART_NUM_0, 1024, 1024, 10, NULL, 0);
}
void Monitor::Run(){
    conPrintf("Monitor starts. Hit [Enter] for help.\n");
    //ShowList();
    while(1){
        uint8_t ch = getchWait();
        int i=0;
        for(; i<(int)commands.size();++i){
            if (commands[i]->Desc()[0] == (char)ch){
                conPrintf("%s\n", commands[i]->Desc());
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

class MCTaskList: public MonitorCommandBase{
    const char* Desc(){ return "t Show task list"; }
    void Func(){
        char buf[1024*2];
        vTaskList(buf);
        conPrintf("Task\t\tState\tPrio\tStack\tNum\n%s\n", buf);
    }
} mcTaskList;
 
class MCEraseNvs: public MonitorCommandBase{
    const char* Desc(){ return "E Erase NVS flash"; }
    void Func(){
        conPrintf("This command erase all NVS flash. Are you sure ? (Y/N)\n");
        while(1){
            int ch = getchNoWait();
            if (ch == 'y' || ch == 'Y'){
#ifndef _WIN32
				nvs_flash_erase();
#endif
				conPrintf("erased.\n");
                break;
            }else if(ch > 0){
                conPrintf("canceled.\n");
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
        conPrintf("[ENTER/SPACE]:show state, [%s]:forward, [%s]:backword, other:quit\n" ,up, down);
        while(1){
            vTaskDelay(10);
            int ch = getchNoWait();
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
                conPrintf("PWM duty = ");
                for(int i=0; i<MotorDriver::NMOTOR_DIRECT; ++i){
                    conPrintf("  %8.1f", duty[i]);
                }
                conPrintf("   Angle =");
                for(int i=0; i<MotorDriver::NMOTOR_DIRECT; ++i){
                    conPrintf("  %8.2f", LDEC2DBL(motorState.pos[i]));
                }
                conPrintf("\n");
            }else{
                break;
            }
            for(int i=0; i<MotorDriver::NMOTOR_DIRECT; ++i){
                motorDriver.Pwm(i, (SDEC)(duty[i] * SDEC_ONE));
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
                conPrintf("%5d\t", raw);
            }
            for(int i=0; i<MotorDriver::NMOTOR_DIRECT; ++i){
                conPrintf("\t%4.2f", LDEC2DBL(motorState.pos[i]));
            }
            conPrintf("\n");
            vTaskDelay(10);
            if (getchNoWait() >= 0) break;
        }
    }
} mcShowADC;

class MCMotorAngleTest: public MonitorCommandBase{
    const char* Desc(){ return "M Motor angle test"; }
    void Func(){
        int dir = 1;
        motorDriver.bControl = false;
        for(int i=0; i<MotorDriver::NMOTOR_DIRECT; ++i){
            motorDriver.Pwm(i, 0);
        }

        conPrintf("Hit Enter key\n\n\n\n");
        if (getchWait() == '\r'){
            for(int d = 0; d<2; ++d){
                for(int i=0; i<MotorDriver::NMOTOR_DIRECT; ++i){
                    motorDriver.Pwm(i, dir * (SDEC)(SDEC_ONE * 0.8) );
                }
                for(int t=0; t<150; ++t){
                    for(int i=0; i<MotorDriver::NMOTOR_DIRECT*2; ++i){
                        int raw = motorDriver.GetAdcRaw(i);
                        conPrintf("%5d\t", raw);
                    }
                    for(int i=0; i<MotorDriver::NMOTOR_DIRECT; ++i){
                        conPrintf("\t%4.2f", LDEC2DBL(motorState.pos[i]));
                    }
                    conPrintf("\n");
                    vTaskDelay(2);
                    if (getchNoWait() >= 0) break;
                }
                dir *= -1;
            }
            for(int i=0; i<MotorDriver::NMOTOR_DIRECT; ++i){
                motorDriver.Pwm(i, 0);
            }
            conPrintf("\n\n\n\nHit any key\n");
            getchWait();
            motorDriver.bControl = true;
        }
    }
} mcMotorAngleTest;


class MCShowTouch: public MonitorCommandBase{
    const char* Desc(){ return "T Show Touch sensors"; }
    void Func(){
        while(1){
            for(int i=0; i<touchPads.NPad(); ++i){
                conPrintf("%d\t", touchPads.Filtered(i));
            }
            conPrintf("\n");
            vTaskDelay(20);
            if (getchNoWait() >= 0) break;
        }
    }
} mcShowTouch;

#ifndef _WIN32
extern "C" void* duk_alloc_hybrid_udata;
extern "C"{
#include "../duktapeEsp32/duk_alloc_hybrid.h"
}
class MCShowHeap: public MonitorCommandBase{
    const char* Desc(){ return "h Show heap memory"; }
    void Func(){
		conPrintf("Heap free size: %d bytes", esp_get_free_heap_size());
        conPrintf(" a:dump all  c:check  m:max free block  t:trace heap  h:hybrid heap\n");
        switch(getchWait()){
            case 'a':
                heap_caps_dump_all();
                break;
            case 'c':
                heap_caps_check_integrity_all(true);
                conPrintf("Heap structure is checked.\n");
                break;
            case 'm':{
                size_t fs = heap_caps_get_largest_free_block(MALLOC_CAP_8BIT);
                conPrintf("Maximum free heap block size with MALLOC_CAP_8BIT is %d = 0x%x.\n", fs, fs);
                fs = heap_caps_get_largest_free_block(MALLOC_CAP_32BIT);
                conPrintf("Maximum free heap block size with MALLOC_CAP_32BIT is %d = 0x%x.\n", fs, fs);
                break;
            }
            case 't':
                heap_trace_dump();
                break;
            case 'h':
                duk_alloc_hybrid_dump(duk_alloc_hybrid_udata);
                break;

        }
	}
} mcShowHeap;
#endif

class MCWriteCmd: public MonitorCommandBase{
    const char* Desc(){ return "w Write command to UART"; }
    void Func(){
        UdpCmdPacket* recv = &udpCom.recvs.Poke();
        recv->command = CI_DIRECT;
        recv->length = recv->CommandLen();
        recv->count = udpCom.commandCount + 1;
        udpCom.recvs.Write();
    }
} mcWriteCmd;

#ifdef _WIN32
class MCShowTask : public MonitorCommandBase {
	const char* Desc() { return "f Show FreeRTOS tasks"; }
	void Func() {
		char buf[1024];
		vTaskList(buf);
		conPrintf("%s", buf);
	}
} mcShowTask;
#endif

extern "C"{
    extern int underflowCount;
}
class MCTargetUnderflow: public MonitorCommandBase{
    const char* Desc(){ return "u Show target underflow"; }
    void Func(){
        while(1){
            int uc = underflowCount;
            underflowCount = 0;
            conPrintf("Underflow count = %d\n", uc);
            vTaskDelay(100);
            if (getchNoWait() >= 0) break;
        }
    }
} mcShowTargetUnderflow;

class MCJSRestart: public MonitorCommandBase{
public:
    MCJSRestart() { bFirst = true; } 
    const char* Desc(){ return "J Restart java script"; }
    bool bFirst;
    void Func(){
        wsDeleteJsfileTask();
        heap_trace_dump();
        if (bFirst){
            heap_trace_start(HEAP_TRACE_LEAKS);
            bFirst = false;
        }
        ESP_LOGI(Tag(), "before wsCreateJsfileTask heap size: %d", esp_get_free_heap_size());
        wsCreateJsfileTask();
        ESP_LOGI(Tag(), "After wsCreateJsfileTask heap size: %d", esp_get_free_heap_size());
    }
} mcJSRestart;

class MCJSStack: public MonitorCommandBase{
public:
    const char* Desc(){ return "j dump java script stack"; }
    void Func(){
        lock_heap();
        duk_context* ctx = esp32_duk_context;
        duk_push_global_object(ctx);
        duk_push_context_dump(ctx);
        printf("%s\n", duk_to_string(ctx, -1));
        duk_pop(ctx);
        duk_pop(ctx);
        unlock_heap();
    }
} mcJSStack;

inline char toLower(char c){
    if ('A' <= c && c <= 'Z'){
        c += 'a'-'A';
    }
    return c;
}
inline char toUpper(char c){
    if ('a' <= c && c <= 'z'){
        c += 'A'-'a';
    }
    return c;
}

class MCLogLevel: public MonitorCommandBase{
public:
    const char* Desc(){ return "l log level set"; }
    void Func(){
        const char levels [] = "NEWIDV";
		conPrintf("Type 'tag level[ENTER]' loglevel='NEWIDV'\n");
		while(1){
            char buf[40];
            getLine(buf, sizeof(buf));
            char* tag = buf;
            while(*tag==' ') tag++;
            char* level = tag;
            while(*level != '\0' && *level != ' ') level++;
            if (*level){
                *level = '\0';
                level++;
            }
            while(*level == ' ') level++;
            for(int l=0; l<sizeof(levels); ++l){
                if (toUpper(level[0]) == levels[l]){
                    if (strlen(tag)){
                        esp_log_level_set(tag, (esp_log_level_t)l);
                        conPrintf("esp_log_level_set(%s, %d)", tag, l);
                        goto next;
                    }
                }
            }
            if (strlen(buf) == 0){
                break;
            }
            next:;
        }
		conPrintf("Back to 'main menu' from 'log level set'\n");
    }
} mcLogLevel;

class MCEspFs: public MonitorCommandBase{
public:
    const char* Desc(){ return "e test Espfs"; }
    void Func(){
        conPrintf("Espfs test w:write, r:read\n");
        switch (getchWait()){
            case 'w':
            case 'W':{
                std::ostream* m_ostream;
                const std::string content = "hello world !!. 0ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "1ABCDEFGHIJKLMNOPQRSTUVWXYZ" "2ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "3ABCDEFGHIJKLMNOPQRSTUVWXYZ" "4ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "5ABCDEFGHIJKLMNOPQRSTUVWXYZ" "6ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "7ABCDEFGHIJKLMNOPQRSTUVWXYZ" "8ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "9ABCDEFGHIJKLMNOPQRSTUVWXYZ" "AABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "BABCDEFGHIJKLMNOPQRSTUVWXYZ" "CABCDEFGHIJKLMNOPQRSTUVWXYZ";
                m_ostream = espFsAddFileByStream("/main/main.js", content.length());
                m_ostream->write(content.c_str(), content.length());
                m_ostream->flush();
                delete m_ostream;
                LOGI("finish writing file");
            }
            break;
            case 'r':
            case 'R':{
                EspFsFile* fh = espFsOpen("/main/main.js");
                if (fh){
                    const char* buf=NULL;
                    size_t len=0;
                    espFsAccess(fh, (void **)&buf, &len);
                    LOGI("file, len=%d, at 0x%x buf=%s", len, (int)buf, buf);
                }
                break;
            }
        }
    }
} mcEspFs;

#include "../../PIC/control.h"
#include "./softRobot/Movement.h"
#include "./softRobot/CommandWROOM.h"

struct MonitorMovementKeyframe {
	uint16_t id;				// 8-bit movement id + 8-bit keyframe id
	uint8_t motorCount;			// count of motors used in the movement
	uint8_t motorId[3];	// the motorIds used
	uint16_t period;			// note that the sum of period in list could not larger than UINT16_MAX (or the sorting might fail)
	short pose[3];			// the poses correspond with motorIds

	uint16_t refId;             // 0 if no ref (movement id should start from 1)
	uint8_t refMotorId;
	short timeOffset;
};

#define struct MonitorMovementKeyframe MonitorMovementKeyframe;

class MCTest: public MonitorCommandBase{
public:
    const char* Desc(){ return "p test movement"; }
    void Func(){
        conPrintf("MCtest\n");
        switch (getchWait()){
            case 'p': {
                printf("target pose: %ld, %ld, %ld \n", motorTarget.pos[0], motorTarget.pos[1], motorTarget.pos[2]);
                break;
            }
            case 'm': {
                printMotorKeyframes(0);
                break;
            }
            case '1': {
                size_t len = 4 + 1 + sizeof(MonitorMovementKeyframe);
                unsigned char motorId[3] = {0, 1, 2};
                short pose[3] = {1000, 0, 0};

                void* payload = (void*)malloc(len);
                *((unsigned short*)payload) = len;
                *((unsigned short*)payload+1) = CIU_MOVEMENT;
                *((unsigned char*)payload+4) = CI_M_ADD_KEYFRAME;
                MonitorMovementKeyframe* keyframe = (MonitorMovementKeyframe*)((unsigned char*)payload+5);
                keyframe->id = 0x0100;
                keyframe->motorCount = 3;
                memcpy(keyframe->motorId, motorId, 3);
                keyframe->period = 6000;
                memcpy(keyframe->pose, pose, 6);
                keyframe->refId = 0x0000;
                keyframe->refMotorId = 0;
                keyframe->timeOffset = 0;

                UdpCom_ReceiveCommand(payload, len, 0);

                break;
            }
            case '2': {
                size_t len = 4 + 1 + sizeof(MonitorMovementKeyframe);
                unsigned char motorId[3] = {0, 1, 2};
                short pose[3] = {-1000, 0, 0};

                void* payload = (void*)malloc(len);
                *((unsigned short*)payload) = len;
                *((unsigned short*)payload+1) = CIU_MOVEMENT;
                *((unsigned char*)payload+4) = CI_M_ADD_KEYFRAME;
                MonitorMovementKeyframe* keyframe = (MonitorMovementKeyframe*)((unsigned char*)payload+5);
                keyframe->id = 0x0100;
                keyframe->motorCount = 3;
                memcpy(keyframe->motorId, motorId, 3);
                keyframe->period = 6000;
                memcpy(keyframe->pose, pose, 6);
                keyframe->refId = 0x0000;
                keyframe->refMotorId = 0;
                keyframe->timeOffset = 0;

                UdpCom_ReceiveCommand(payload, len, 0);

                break;
            }
        }
    }
} mcTest;

