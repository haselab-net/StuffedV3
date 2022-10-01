#include "definitions.h"
#include "initMk.h"
#include "device.h"
#include "mkCoreTimer.h"
#include "controlPic.h"

#define ADC_VREF                (3.3f)
#define ADC_MAX_COUNT           (4095)


void coretimerCallback(uint32_t st, uintptr_t arg){
    CORETIMER_Start();
    onControlTimer();
    ADCHS_GlobalEdgeConversionStart();
}

//  init all
void initMk(){
    SYS_Initialize(NULL);
    CORETIMER_Initialize();
    ADCCON1bits.STRGSRC = 1;    //  00010 = Global level software trigger (GLSWTRG) is not self-cleared
                                //  00001 = Global software trigger (GSWTRG) is self-cleared on the next clock cycle

    CORETIMER_CallbackSet(coretimerCallback, NULL);
    CORETIMER_Start();
    
    MCPWM_Start();
}