
/**
  ADC1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    adc1.c

  @Summary
    This is the generated header file for the ADC1 driver using Foundation Services Library

  @Description
    This header file provides APIs for driver for ADC1.
    Generation Information :
        Product Revision  :  Foundation Services Library - pic24-dspic-pic32mm : v1.26
        Device            :  PIC32MM0064GPL036
    The generated drivers are tested against the following:
        Compiler          :  XC32 1.42
        MPLAB 	          :  MPLAB X 3.45
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
#include "adc1.h"

/**
  Section: Data Type Definitions
*/

/* ADC Driver Hardware Instance Object

  @Summary
    Defines the object required for the maintenance of the hardware instance.

  @Description
    This defines the object required for the maintenance of the hardware
    instance. This object exists once per hardware instance of the peripheral.

 */
typedef struct
{
	uint8_t intSample;
}

ADC_OBJECT;

static ADC_OBJECT adc1_obj;

/**
  Section: Driver Interface
*/


void ADC1_Initialize (void)
{
    // ASAM enabled; DONE disabled; FORM Integer 16-bit; SAMP disabled; SSRC Internal counter ends sampling and starts conversion; SIDL disabled; MODE12 12-bit; ON enabled; 

   AD1CON1 = 0x807C;

    // CSCNA enabled; BUFM disabled; SMPI 12; OFFCAL disabled; VCFG AVDD/AVSS; BUFREGEN disabled; 
#if defined BOARD1_MOTORDRIVER
   AD1CON2 = 0x420; //  Range=AVDD-AVSS, OFFCAL=0, BUF=FIFO, Scan input, 8samples,  16bitBUF,
#elif defined BOARD2_COMBINATION || defined BOARD3_SEPARATE
   AD1CON2 = 0x430; //  Range=AVDD-AVSS, OFFCAL=0, BUF=FIFO, Scan input, 12samples,  16bitBUF,
#else
#error
#endif
    // SAMC 31; EXTSAM disabled; ADRC PBCLK; ADCS 3; 
   AD1CON3 = 0x1F03;

   // CH0SA AN0; CH0NA AVSS;
   AD1CHS = 0x0;

#if defined BOARD1_MOTORDRIVER
    // CSS9 disabled; CSS8 enabled; CSS7 enabled; CSS6 disabled; CSS5 disabled; CSS4 enabled; CSS3 disabled; CSS2 disabled; CSS1 enabled; CSS0 enabled; CSS13 enabled; CSS12 enabled; CSS11 enabled; CSS10 disabled; CSS30 disabled; CSS29 disabled; CSS28 disabled; 
   AD1CSS = 0x3993;
#elif defined BOARD2_COMBINATION || defined BOARD3_SEPARATE
    // CSS9 disabled; CSS8 enabled; CSS7 enabled; CSS6 disabled; CSS5 enabled; CSS4 enabled; CSS3 enabled; CSS2 enabled; CSS1 enabled; CSS0 enabled; CSS13 enabled; CSS12 enabled; CSS11 enabled; CSS10 enabled; CSS30 disabled; CSS29 disabled; CSS28 disabled;
    AD1CSS = 0x3DBF;
#else
#error
#endif
   // CHH9 disabled; CHH8 disabled; CHH7 disabled; CHH6 disabled; CHH5 disabled; CHH4 disabled; CHH3 disabled; CHH2 disabled; CHH1 disabled; CHH0 disabled; CHH11 disabled; CHH10 disabled; CHH13 disabled; CHH12 disabled; 
   AD1CHIT = 0x0;

   adc1_obj.intSample = AD1CON2bits.SMPI;
   
}

void ADC1_Start(void)
{
   AD1CON1SET = (1 << _AD1CON1_SAMP_POSITION);
}
void ADC1_Stop(void)
{
   AD1CON1CLR = (1 << _AD1CON1_SAMP_POSITION);
}
uint16_t ADC1_ConversionResultBufferGet(uint16_t *buffer)
{
    int count;
    uint16_t *ADC16Ptr;

    ADC16Ptr = (uint16_t *)&(ADC1BUF0);

    for(count=0;count<=adc1_obj.intSample;count++)
    {
        buffer[count] = (uint16_t)*ADC16Ptr;
        ADC16Ptr++;
    }
    return count;
}
uint16_t ADC1_ConversionResultGet(void)
{
    return ADC1BUF0;
}
bool ADC1_IsConversionComplete( void )
{
    return AD1CON1bits.DONE; //Wait for conversion to complete   
}
void ADC1_ChannelSelect( ADC1_CHANNEL channel )
{
    AD1CHS = channel;
}

uint16_t ADC1_GetConversion(ADC1_CHANNEL channel)
{
    ADC1_ChannelSelect(channel);
    
    ADC1_Start();
    ADC1_Stop();
    
    while (!ADC1_IsConversionComplete())
    {
    }
       
    return ADC1_ConversionResultGet();
}


void ADC1_Tasks ( void )
{
    // clear the ADC interrupt flag
    IFS0CLR= 1 << _IFS0_AD1IF_POSITION;
}


/**
  End of File
*/
