
/**
  CORETIMER Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
   coretimer.c

  @Summary
    This is the generated driver implementation file for the CORETIMER driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides implementations for driver APIs for CORETIMER.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : v1.45
        Device            :  PIC32MM0064GPL036
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC32 1.43
        MPLAB             :  MPLAB X 3.61
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "coretimer.h"

/**
  Section: Core Timer Module APIs
*/

uint32_t coretimerCompare = 0x2EE0;
void CORETIMER_Initialize()
{
   // Set the count value
   _CP0_SET_COUNT(0x0); 
   // Set the coretimerCompare value
	coretimerCompare = 0x2EE0;
	_CP0_SET_COMPARE(coretimerCompare); 
    // Enable the interrupt
   IEC0bits.CTIE = 1;
}

void CORETIMER_EnableInterrupt()
{
    IEC0bits.CTIE = 1;
}

void CORETIMER_DisableInterrupt()
{
    IEC0bits.CTIE = 0;
}

uint32_t CORETIMER_CountGet()
{
   return _CP0_GET_COUNT();
}

int coretimerRemainTime;
void __attribute__ ((vector(_CORE_TIMER_VECTOR), interrupt(IPL1SOFT))) _CORE_TIMER_ISR(void)
{
	// Update the coretimerCompare value
	//coretimerCompare = coretimerCompare + 12000;	//	12MHz/12k = 1kHz
	coretimerCompare = coretimerCompare + 4000;		//	12MHz/4k = 3kHz may be maximum.
	_CP0_SET_COMPARE(coretimerCompare);
	IFS0CLR= 1 << _IFS0_CTIF_POSITION;
	//	Control task
	onControlTimer();
	uint32_t now = _CP0_GET_COUNT();
	coretimerRemainTime = coretimerCompare - now;
}

/**
 End of File
*/
