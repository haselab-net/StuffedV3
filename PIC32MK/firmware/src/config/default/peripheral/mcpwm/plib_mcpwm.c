/*******************************************************************************
  Motor Control PWM (MCPWM) Peripheral Library (PLIB)

  Company:
    Microchip Technology Inc.

  File Name:
    plib_mcpwm.c

  Summary:
    MCPWM Source File

  Description:
    None

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
#include "device.h"
#include "plib_mcpwm.h"
#include "interrupts.h"

// *****************************************************************************

// *****************************************************************************
// Section: MCPWM Implementation
// *****************************************************************************
// *****************************************************************************

void MCPWM_Initialize (void)
{
    /* PTCON register  */
    /*  SEVTPS  = 0 */
    /*  PCLKDIV = 0 */
    /*  SEIEN   = false */
    PTCON = 0x0;

    /* STCON register  */
    /*  SEVTPS  = 0 */
    /*  SCLKDIV = 0 */
    /*  SSEIEN = false */
    STCON = 0x0;

    PTPER = 50;
    STPER = 2000;
    SEVTCMP = 0;
    SSEVTCMP = 10;

    /*********** Channel 1 Configurations **********/
    /* PWMCON1 register  */
    /*  MTBS   = 0 */
    /*  PTDIR  =  0 */
    /*  ECAM   =  0 */
    /*  DTCP   =  0 */
    /*  DTC    =  2 */
    /*  ITB    = 0 */
    /*  PWMHIEN =  false */
    /*  PWMLIEN = false */
    /*  TRGIEN = false */
    /*  CLIEN = false */
    /*  FLTIEN = false */
    PWMCON1 = 0x80;

    /* IOCON1 register  */
    /*  SWAP    = 0*/
    /*  PMOD    = 1*/
    /*  POLH    = 0*/
    /*  POLL    = 0*/
    /*  FLTDAT  = 0b00 */
    /*  FLTMOD  = 3 */
    /*  PENH  = 1 */
    /*  PENL  = 1 */
    /*  FLTPOL  = 0  */
    /*  FLTSRC  = 0  */
    /*  CLDAT  = 0b00 */
    /*  CLMOD  = 0 */
    /*  CLPOL  = 0  */
    /*  CLSRC  = 0  */
    IOCON1 = 0x3c400;

    PDC1 = 1000;
    SDC1 = 500;
    PHASE1 = 0;

    /* Dead Time */
    DTR1 = 0;
    ALTDTR1 = 0;

    /* Trigger Generator */
    TRGCON1 = 0x0;
    TRIG1 = 0;
    STRIG1 = 0;

    /* leading edge blanking */
    /* LEBCON1 register  */
    /*  CLLEBEN    = false  */
    /*  FLTLEBEN   = false */
    /*  PLF        = 0  */
    /*  PLR        = 0  */
    /*  PHF        = 0  */
    /*  PHR        = 0  */
    LEBCON1 = 0x0;
    LEBDLY1 = 0;


    /*********** Channel 2 Configurations **********/
    /* PWMCON2 register  */
    /*  MTBS   = 0 */
    /*  PTDIR  =  0 */
    /*  ECAM   =  0 */
    /*  DTCP   =  0 */
    /*  DTC    =  2 */
    /*  ITB    = 0 */
    /*  PWMHIEN =  false */
    /*  PWMLIEN = false */
    /*  TRGIEN = false */
    /*  CLIEN = false */
    /*  FLTIEN = false */
    PWMCON2 = 0x80;

    /* IOCON2 register  */
    /*  SWAP    = 0*/
    /*  PMOD    = 1*/
    /*  POLH    = 0*/
    /*  POLL    = 0*/
    /*  FLTDAT  = 0b00 */
    /*  FLTMOD  = 3 */
    /*  PENH  = 1 */
    /*  PENL  = 1 */
    /*  FLTPOL  = 0  */
    /*  FLTSRC  = 0  */
    /*  CLDAT  = 0b00 */
    /*  CLMOD  = 0 */
    /*  CLPOL  = 0  */
    /*  CLSRC  = 0  */
    IOCON2 = 0x3c400;

    PDC2 = 1000;
    SDC2 = 500;
    PHASE2 = 0;

    /* Dead Time */
    DTR2 = 0;
    ALTDTR2 = 0;

    /* Trigger Generator */
    TRGCON2 = 0x0;
    TRIG2 = 0;
    STRIG2 = 0;

    /* leading edge blanking */
    /* LEBCON2 register  */
    /*  CLLEBEN    = false  */
    /*  FLTLEBEN   = false */
    /*  PLF        = 0  */
    /*  PLR        = 0  */
    /*  PHF        = 0  */
    /*  PHR        = 0  */
    LEBCON2 = 0x0;
    LEBDLY2 = 10;


    /*********** Channel 3 Configurations **********/
    /* PWMCON3 register  */
    /*  MTBS   = 0 */
    /*  PTDIR  =  0 */
    /*  ECAM   =  0 */
    /*  DTCP   =  0 */
    /*  DTC    =  2 */
    /*  ITB    = 0 */
    /*  PWMHIEN =  false */
    /*  PWMLIEN = false */
    /*  TRGIEN = false */
    /*  CLIEN = false */
    /*  FLTIEN = false */
    PWMCON3 = 0x80;

    /* IOCON3 register  */
    /*  SWAP    = 0*/
    /*  PMOD    = 1*/
    /*  POLH    = 0*/
    /*  POLL    = 0*/
    /*  FLTDAT  = 0b00 */
    /*  FLTMOD  = 3 */
    /*  PENH  = 1 */
    /*  PENL  = 1 */
    /*  FLTPOL  = 0  */
    /*  FLTSRC  = 0  */
    /*  CLDAT  = 0b00 */
    /*  CLMOD  = 0 */
    /*  CLPOL  = 0  */
    /*  CLSRC  = 0  */
    IOCON3 = 0x3c400;

    PDC3 = 1000;
    SDC3 = 500;
    PHASE3 = 0;

    /* Dead Time */
    DTR3 = 0;
    ALTDTR3 = 0;

    /* Trigger Generator */
    TRGCON3 = 0x0;
    TRIG3 = 0;
    STRIG3 = 0;

    /* leading edge blanking */
    /* LEBCON3 register  */
    /*  CLLEBEN    = false  */
    /*  FLTLEBEN   = false */
    /*  PLF        = 0  */
    /*  PLR        = 0  */
    /*  PHF        = 0  */
    /*  PHR        = 0  */
    LEBCON3 = 0x0;
    LEBDLY3 = 10;


    /*********** Channel 4 Configurations **********/
    /* PWMCON4 register  */
    /*  MTBS   = 0 */
    /*  PTDIR  =  0 */
    /*  ECAM   =  0 */
    /*  DTCP   =  0 */
    /*  DTC    =  2 */
    /*  ITB    = 0 */
    /*  PWMHIEN =  false */
    /*  PWMLIEN = false */
    /*  TRGIEN = false */
    /*  CLIEN = false */
    /*  FLTIEN = false */
    PWMCON4 = 0x80;

    /* IOCON4 register  */
    /*  SWAP    = 0*/
    /*  PMOD    = 1*/
    /*  POLH    = 0*/
    /*  POLL    = 0*/
    /*  FLTDAT  = 0b00 */
    /*  FLTMOD  = 3 */
    /*  PENH  = 1 */
    /*  PENL  = 1 */
    /*  FLTPOL  = 0  */
    /*  FLTSRC  = 0  */
    /*  CLDAT  = 0b00 */
    /*  CLMOD  = 0 */
    /*  CLPOL  = 0  */
    /*  CLSRC  = 0  */
    IOCON4 = 0x3c400;

    PDC4 = 1000;
    SDC4 = 500;
    PHASE4 = 0;

    /* Dead Time */
    DTR4 = 0;
    ALTDTR4 = 0;

    /* Trigger Generator */
    TRGCON4 = 0x0;
    TRIG4 = 0;
    STRIG4 = 0;

    /* leading edge blanking */
    /* LEBCON4 register  */
    /*  CLLEBEN    = false  */
    /*  FLTLEBEN   = false */
    /*  PLF        = 0  */
    /*  PLR        = 0  */
    /*  PHF        = 0  */
    /*  PHR        = 0  */
    LEBCON4 = 0x0;
    LEBDLY4 = 10;


    /*********** Channel 5 Configurations **********/
    /* PWMCON5 register  */
    /*  MTBS   = 0 */
    /*  PTDIR  =  0 */
    /*  ECAM   =  0 */
    /*  DTCP   =  0 */
    /*  DTC    =  2 */
    /*  ITB    = 0 */
    /*  PWMHIEN =  false */
    /*  PWMLIEN = false */
    /*  TRGIEN = false */
    /*  CLIEN = false */
    /*  FLTIEN = false */
    PWMCON5 = 0x80;

    /* IOCON5 register  */
    /*  SWAP    = 0*/
    /*  PMOD    = 1*/
    /*  POLH    = 0*/
    /*  POLL    = 0*/
    /*  FLTDAT  = 0b00 */
    /*  FLTMOD  = 3 */
    /*  PENH  = 1 */
    /*  PENL  = 1 */
    /*  FLTPOL  = 0  */
    /*  FLTSRC  = 0  */
    /*  CLDAT  = 0b00 */
    /*  CLMOD  = 0 */
    /*  CLPOL  = 0  */
    /*  CLSRC  = 0  */
    IOCON5 = 0x3c400;

    PDC5 = 1000;
    SDC5 = 500;
    PHASE5 = 0;

    /* Dead Time */
    DTR5 = 0;
    ALTDTR5 = 0;

    /* Trigger Generator */
    TRGCON5 = 0x0;
    TRIG5 = 0;
    STRIG5 = 0;

    /* leading edge blanking */
    /* LEBCON5 register  */
    /*  CLLEBEN    = false  */
    /*  FLTLEBEN   = false */
    /*  PLF        = 0  */
    /*  PLR        = 0  */
    /*  PHF        = 0  */
    /*  PHR        = 0  */
    LEBCON5 = 0x0;
    LEBDLY5 = 10;


    /*********** Channel 6 Configurations **********/
    /* PWMCON6 register  */
    /*  MTBS   = 0 */
    /*  PTDIR  =  0 */
    /*  ECAM   =  0 */
    /*  DTCP   =  0 */
    /*  DTC    =  2 */
    /*  ITB    = 0 */
    /*  PWMHIEN =  false */
    /*  PWMLIEN = false */
    /*  TRGIEN = false */
    /*  CLIEN = false */
    /*  FLTIEN = false */
    PWMCON6 = 0x80;

    /* IOCON6 register  */
    /*  SWAP    = 0*/
    /*  PMOD    = 1*/
    /*  POLH    = 0*/
    /*  POLL    = 0*/
    /*  FLTDAT  = 0b00 */
    /*  FLTMOD  = 3 */
    /*  PENH  = 1 */
    /*  PENL  = 1 */
    /*  FLTPOL  = 0  */
    /*  FLTSRC  = 0  */
    /*  CLDAT  = 0b00 */
    /*  CLMOD  = 0 */
    /*  CLPOL  = 0  */
    /*  CLSRC  = 0  */
    IOCON6 = 0x3c400;

    PDC6 = 1000;
    SDC6 = 500;
    PHASE6 = 0;

    /* Dead Time */
    DTR6 = 0;
    ALTDTR6 = 0;

    /* Trigger Generator */
    TRGCON6 = 0x0;
    TRIG6 = 0;
    STRIG6 = 0;

    /* leading edge blanking */
    /* LEBCON6 register  */
    /*  CLLEBEN    = false  */
    /*  FLTLEBEN   = false */
    /*  PLF        = 0  */
    /*  PLR        = 0  */
    /*  PHF        = 0  */
    /*  PHR        = 0  */
    LEBCON6 = 0x0;
    LEBDLY6 = 10;


    /*********** Channel 7 Configurations **********/
    /* PWMCON7 register  */
    /*  MTBS   = 0 */
    /*  PTDIR  =  0 */
    /*  ECAM   =  0 */
    /*  DTCP   =  0 */
    /*  DTC    =  2 */
    /*  ITB    = 0 */
    /*  PWMHIEN =  false */
    /*  PWMLIEN = false */
    /*  TRGIEN = false */
    /*  CLIEN = false */
    /*  FLTIEN = false */
    PWMCON7 = 0x80;

    /* IOCON7 register  */
    /*  SWAP    = 0*/
    /*  PMOD    = 1*/
    /*  POLH    = 0*/
    /*  POLL    = 0*/
    /*  FLTDAT  = 0b00 */
    /*  FLTMOD  = 3 */
    /*  PENH  = 1 */
    /*  PENL  = 1 */
    /*  FLTPOL  = 0  */
    /*  FLTSRC  = 0  */
    /*  CLDAT  = 0b00 */
    /*  CLMOD  = 0 */
    /*  CLPOL  = 0  */
    /*  CLSRC  = 0  */
    IOCON7 = 0x3c400;

    PDC7 = 1000;
    SDC7 = 500;
    PHASE7 = 0;

    /* Dead Time */
    DTR7 = 0;
    ALTDTR7 = 0;

    /* Trigger Generator */
    TRGCON7 = 0x0;
    TRIG7 = 0;
    STRIG7 = 0;

    /* leading edge blanking */
    /* LEBCON7 register  */
    /*  CLLEBEN    = false  */
    /*  FLTLEBEN   = false */
    /*  PLF        = 0  */
    /*  PLR        = 0  */
    /*  PHF        = 0  */
    /*  PHR        = 0  */
    LEBCON7 = 0x0;
    LEBDLY7 = 10;


    /*********** Channel 8 Configurations **********/
    /* PWMCON8 register  */
    /*  MTBS   = 0 */
    /*  PTDIR  =  0 */
    /*  ECAM   =  0 */
    /*  DTCP   =  0 */
    /*  DTC    =  2 */
    /*  ITB    = 0 */
    /*  PWMHIEN =  false */
    /*  PWMLIEN = false */
    /*  TRGIEN = false */
    /*  CLIEN = false */
    /*  FLTIEN = false */
    PWMCON8 = 0x80;

    /* IOCON8 register  */
    /*  SWAP    = 0*/
    /*  PMOD    = 1*/
    /*  POLH    = 0*/
    /*  POLL    = 0*/
    /*  FLTDAT  = 0b00 */
    /*  FLTMOD  = 3 */
    /*  PENH  = 1 */
    /*  PENL  = 1 */
    /*  FLTPOL  = 0  */
    /*  FLTSRC  = 0  */
    /*  CLDAT  = 0b00 */
    /*  CLMOD  = 0 */
    /*  CLPOL  = 0  */
    /*  CLSRC  = 0  */
    IOCON8 = 0x3c400;

    PDC8 = 1000;
    SDC8 = 500;
    PHASE8 = 0;

    /* Dead Time */
    DTR8 = 0;
    ALTDTR8 = 0;

    /* Trigger Generator */
    TRGCON8 = 0x0;
    TRIG8 = 0;
    STRIG8 = 0;

    /* leading edge blanking */
    /* LEBCON8 register  */
    /*  CLLEBEN    = false  */
    /*  FLTLEBEN   = false */
    /*  PLF        = 0  */
    /*  PLR        = 0  */
    /*  PHF        = 0  */
    /*  PHR        = 0  */
    LEBCON8 = 0x0;
    LEBDLY8 = 10;


}


void MCPWM_Start(void)
{
    /* Enable MCPWM module */
    PTCONbits.PTEN = 0x1;
}

void MCPWM_Stop(void)
{
    /* Disable MCPWM module */
    PTCONbits.PTEN = 0x0;
}

void MCPWM_PrimaryPeriodSet(uint16_t period)
{
    PTPER = period;
}

uint16_t MCPWM_PrimaryPeriodGet(void)
{
    return (uint16_t)PTPER;
}


void MCPWM_SecondaryPeriodSet(uint16_t period)
{
    STPER = period;
}

uint16_t MCPWM_SecondaryPeriodGet(void)
{
    return (uint16_t)STPER;
}

void MCPWM_ChannelPrimaryDutySet(MCPWM_CH_NUM channel, uint16_t duty)
{
    *(&PDC1 + (0x40U * (channel))) = duty;
}

void MCPWM_ChannelSecondaryDutySet(MCPWM_CH_NUM channel, uint16_t duty)
{
    *(&SDC1 + (0x40U * (channel))) = duty;
}

void MCPWM_ChannelDeadTimeSet(MCPWM_CH_NUM channel, uint16_t high_deadtime, uint16_t low_deadtime)
{
    *(&DTR1 + (0x40U * (channel))) = ((uint32_t)high_deadtime & (uint32_t)0x3FFFU);
    *(&ALTDTR1 + (0x40U * (channel))) = ((uint32_t)low_deadtime & (uint32_t)0x3FFFU);
}

void MCPWM_ChannelPrimaryTriggerSet(MCPWM_CH_NUM channel, uint16_t trigger)
{
    *(&TRIG1 + (0x40U * (channel))) = trigger;
}

void MCPWM_ChannelSecondaryTriggerSet(MCPWM_CH_NUM channel, uint16_t trigger)
{
    *(&STRIG1 + (0x40U * (channel))) = trigger;
}

void MCPWM_ChannelLeadingEdgeBlankingDelaySet(MCPWM_CH_NUM channel, uint16_t delay)
{
    *(&LEBDLY1 + (0x40U * (channel))) = delay;
}

void MCPWM_ChannelPinsOverrideEnable(MCPWM_CH_NUM channel)
{
    *(&IOCON1 + (0x40U * (channel))) |= _IOCON1_OVRENL_MASK | _IOCON1_OVRENH_MASK;
}

void MCPWM_ChannelPinsOverrideDisable(MCPWM_CH_NUM channel)
{
    *(&IOCON1 + (0x40U * (channel))) &= ~(_IOCON1_OVRENL_MASK | _IOCON1_OVRENH_MASK);
}

void MCPWM_ChannelPinsOwnershipEnable(MCPWM_CH_NUM channel)
{
    *(&IOCON1 + (0x40U * (channel))) |= _IOCON1_PENH_MASK | _IOCON1_PENL_MASK;
}

void MCPWM_ChannelPinsOwnershipDisable(MCPWM_CH_NUM channel)
{
    *(&IOCON1 + (0x40U * (channel))) &= ~(_IOCON1_PENH_MASK | _IOCON1_PENL_MASK);
}




