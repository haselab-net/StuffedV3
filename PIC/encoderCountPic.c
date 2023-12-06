#include "env.h"

#include "fixed.h"
#include "control.h"
#ifdef PIC32MM
#include "mcc_generated_files/mcc.h"
#else
#include "definitions.h"
#endif
#include "nvm.h"
#include <assert.h>
#include "controlPic.h"

void initEncoder(){
#if defined PIC32MK_MCJ
    //  Bits of encoderFlags mean 0:Magnet sensro=ADC, 1:encoder=digital.
    //  Clear = set all magnet.
    ANSELA = 0xFFFFU;   //  1:ADC 1:Digital
    ANSELB = 0xFFFFU;
    ANSELC = 0xFFFFU;
    ANSELE = 0xFFFFU;
    unsigned int anselACLR = 0x8000U;
    unsigned int anselBCLR = 0x280U;
    unsigned int anselCCLR = 0x1400U;
    unsigned int anselECLR = 0x0U;
    //  No interrupt for software counters.
    GPIO_PinIntDisable(GPIO_PIN_RB0);
    GPIO_PinIntDisable(GPIO_PIN_RB1);
    GPIO_PinIntDisable(GPIO_PIN_RB2);
    GPIO_PinIntDisable(GPIO_PIN_RB3);        
    GPIO_PinIntDisable(GPIO_PIN_RC0);
    GPIO_PinIntDisable(GPIO_PIN_RC1);                
    GPIO_PinIntDisable(GPIO_PIN_RC2);
    GPIO_PinIntDisable(GPIO_PIN_RC11);                        
    GPIO_PinIntDisable(GPIO_PIN_RE12);
    GPIO_PinIntDisable(GPIO_PIN_RE13);
    
    //  start three hardware encoder counters.
    QEI1_Start();
    QEI2_Start();
    QEI3_Start();

    if (encoderFlags & (1<<0)) anselACLR |= 0x1800; // RA11,12  Use QEI1
    if (encoderFlags & (1<<1)) anselACLR |= 0x0003; // RA0,1    Use QEI3
    if (encoderFlags & (1<<2)){
        anselBCLR |= 0x0003; // RB0,1
        GPIO_PinInputEnable(GPIO_PIN_RB0);
        GPIO_PinInputEnable(GPIO_PIN_RB1);
        GPIO_PinIntEnable(GPIO_PIN_RB0, GPIO_INTERRUPT_ON_BOTH_EDGES);
        GPIO_PinIntEnable(GPIO_PIN_RB1, GPIO_INTERRUPT_ON_BOTH_EDGES);
    } 
    if (encoderFlags & (1<<3)){
        anselBCLR |= 0x000C; // RB2,3
        GPIO_PinInputEnable(GPIO_PIN_RB2);
        GPIO_PinInputEnable(GPIO_PIN_RB2);
        GPIO_PinIntEnable(GPIO_PIN_RB2, GPIO_INTERRUPT_ON_BOTH_EDGES);
        GPIO_PinIntEnable(GPIO_PIN_RB3, GPIO_INTERRUPT_ON_BOTH_EDGES);        
    }
    if (encoderFlags & (1<<4)){
        anselCCLR |= 0x0003; // RC0,1
        GPIO_PinInputEnable(GPIO_PIN_RC0);
        GPIO_PinInputEnable(GPIO_PIN_RC1);
        GPIO_PinIntEnable(GPIO_PIN_RC0, GPIO_INTERRUPT_ON_BOTH_EDGES);
        GPIO_PinIntEnable(GPIO_PIN_RC1, GPIO_INTERRUPT_ON_BOTH_EDGES);                
    }
    if (encoderFlags & (1<<5)){
        anselCCLR |= 0x0804; // RC2,11    
        GPIO_PinInputEnable(GPIO_PIN_RC2);
        GPIO_PinInputEnable(GPIO_PIN_RC11);
        GPIO_PinIntEnable(GPIO_PIN_RC2, GPIO_INTERRUPT_ON_BOTH_EDGES);
        GPIO_PinIntEnable(GPIO_PIN_RC11, GPIO_INTERRUPT_ON_BOTH_EDGES);                        
    }
    if (encoderFlags & (1<<6)){
        anselECLR |= 0x3000; // RE12,13    
        GPIO_PinInputEnable(GPIO_PIN_RE12);
        GPIO_PinInputEnable(GPIO_PIN_RE13);
        GPIO_PinIntEnable(GPIO_PIN_RE12, GPIO_INTERRUPT_ON_BOTH_EDGES);
        GPIO_PinIntEnable(GPIO_PIN_RE13, GPIO_INTERRUPT_ON_BOTH_EDGES);                        
    }
    if (encoderFlags & (1<<7)) anselECLR |= 0xC000; // RE14,15  Use QEI2
    ANSELACLR = anselACLR;
    ANSELBCLR = anselBCLR;
    ANSELCCLR = anselCCLR;
    ANSELECLR = anselECLR;
    printf("Digital: A=%x, B=%x, C=%x, E=%x\r\n", anselACLR, anselBCLR, anselCCLR, anselECLR);

    /*
    //  RB3
    ANSELBSET = 0x08;
    CNPUBSET = 0x08; // Pull-Up Enable
    TRISBCLR = 0x08;    //  output
    LATBSET = 0x08; //  HI
    */

#endif
}



#ifdef PIC32MK_MCJ
#define INC_COND(x, y)  (((x)&&(y)) || ((x)==0&&(y)==0))
void CHANGE_NOTICE_B_InterruptHandlerForEncoder(){
    int status  = CNSTATB;
    int port = PORTB;
    IFS1CLR = _IFS1_CNBIF_MASK;
    if (status & 0x01) qeCount[2] += INC_COND(port&0x01, port&0x02) ? 1 : -1;
    if (status & 0x02) qeCount[2] += !INC_COND(port&0x01, port&0x02) ? 1 : -1;
    if (status & 0x04) qeCount[3] += INC_COND(port&0x04, port&0x08) ? 1 : -1;
    if (status & 0x08) qeCount[3] += !INC_COND(port&0x04, port&0x08) ? 1 : -1;    
    //printf("BI s:%x p:%x\n", status, port);
}
void CHANGE_NOTICE_C_InterruptHandlerForEncoder(){
    int status  = CNSTATC;
    int port = PORTC;
    IFS1CLR = _IFS1_CNCIF_MASK;
    if (status & 0x01) qeCount[4] += INC_COND(port&0x01, port&0x02) ? 1 : -1;
    if (status & 0x02) qeCount[4] += !INC_COND(port&0x01, port&0x02) ? 1 : -1;
    if (status & 0x04) qeCount[5] += INC_COND(port&0x04, port&0x800) ? 1 : -1;
    if (status & 0x800) qeCount[5] += !INC_COND(port&0x04, port&0x800) ? 1 : -1;    
}
void CHANGE_NOTICE_E_InterruptHandlerForEncoder(){
    int status  = CNSTATE;
    int port = PORTE;
    IFS1CLR = _IFS1_CNEIF_MASK;
    if (status & 0x1000) qeCount[6] += INC_COND(port&0x1000, port&0x2000) ? 1 : -1;
    if (status & 0x2000) qeCount[6] += !INC_COND(port&0x1000, port&0x2000) ? 1 : -1;
}

#endif
