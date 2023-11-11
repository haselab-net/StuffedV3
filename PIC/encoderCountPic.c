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

#ifdef PIC32MK_MCJ
#define INC_COND(x, y)  (((x)&&(y)) || ((x)==0&&(y)==0))
void CHANGE_NOTICE_B_InterruptHandlerForEncoder(){
    int status  = CNSTATB;
    int port = PORTB;
    if (status & 0x01) qeCount[2] += INC_COND(port&0x01, port&0x02) ? 1 : -1;
    if (status & 0x02) qeCount[2] += !INC_COND(port&0x01, port&0x02) ? 1 : -1;
    if (status & 0x04) qeCount[3] += INC_COND(port&0x04, port&0x08) ? 1 : -1;
    if (status & 0x08) qeCount[3] += !INC_COND(port&0x04, port&0x08) ? 1 : -1;    
    IFS1CLR = _IFS1_CNBIF_MASK;
}
void CHANGE_NOTICE_C_InterruptHandlerForEncoder(){
    int status  = CNSTATC;
    int port = PORTC;
    if (status & 0x01) qeCount[4] += INC_COND(port&0x01, port&0x02) ? 1 : -1;
    if (status & 0x02) qeCount[4] += !INC_COND(port&0x01, port&0x02) ? 1 : -1;
    if (status & 0x04) qeCount[5] += INC_COND(port&0x04, port&0x800) ? 1 : -1;
    if (status & 0x800) qeCount[6] += !INC_COND(port&0x04, port&0x800) ? 1 : -1;    
    IFS1CLR = _IFS1_CNCIF_MASK;
}
void CHANGE_NOTICE_E_InterruptHandlerForEncoder(){
    int status  = CNSTATE;
    int port = PORTE;
    if (status & 0x1000) qeCount[7] += INC_COND(port&0x1000, port&0x2000) ? 1 : -1;
    if (status & 0x2000) qeCount[7] += !INC_COND(port&0x1000, port&0x2000) ? 1 : -1;
    IFS1CLR = _IFS1_CNEIF_MASK;
}

#endif
