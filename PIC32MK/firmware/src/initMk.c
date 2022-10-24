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


void initInterrupt(){
    // Enable Multi Vector Configuration
    INTCONbits.MVEC = 1;
    
    //	UART to commucate with the main board
	IPC_UCRXIP = 4;	//	receive first
	IPC_UCRXIS = 0; 
	IPC_UCTXIP = 2;	//	then send
	IPC_UCTXIS = 0;

	//    CTI: Core Timer
    IPC0bits.CTIP = 1;
    IPC0bits.CTIS = 0;

    //    TI: Timer 1
    IPC1bits.T1IP = 3;
    IPC1bits.T1IS = 0;
}


//  init all
void initMk(){
    SYS_Initialize(NULL);
    initInterrupt();
    
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
    GPIO_RB9_Clear();

}
