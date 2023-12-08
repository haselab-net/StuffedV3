#include "definitions.h"
#include "initMk.h"
#include "device.h"
#include "controlPic.h"
#include "uart.h"


#define ADC_VREF                (3.3f)
#define ADC_MAX_COUNT           (4095)

int coretimerRemainTime;

void tmr2CallBack(uint32_t st, uintptr_t arg){
    onControlTimer();
    ADCHS_GlobalEdgeConversionStart();
    coretimerRemainTime = TMR2_PeriodGet() - TMR2_CounterGet();
}


//  init all
void initMk(){
    SYS_Initialize(NULL);
    
    /*
    char msg1[] = "Initial UART2 Write Test.\r\n";
    UART2_Write(msg1, sizeof(msg1));    

    char buf[4];
    UART2_Read(buf, sizeof(buf));
    UART2_Write("\r\n", 2);
    UART2_Write(buf, sizeof(buf));
    UART2_Write("\r\n", 2);
*/
    ADCCON1bits.STRGSRC = 1;    //  00010 = Global level software trigger (GLSWTRG) is not self-cleared
                                //  00001 = Global software trigger (GSWTRG) is self-cleared on the next clock cycle
    
    TMR2_CallbackRegister(tmr2CallBack, NULL);
    TMR2_Start();

    TMR1_Start();
    
    MCPWM_Start();
    IOCON9bits.PENL = 0;    //  PWM8L should be GPIO
    GPIO_RB9_Set();         //  LED ON
}
