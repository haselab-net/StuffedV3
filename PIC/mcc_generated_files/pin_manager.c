/**
  System Interrupts Generated Driver File 

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.c

  @Summary:
    This is the generated manager file for the MPLAB(c) Code Configurator device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description:
    This source file provides implementations for MPLAB(c) Code Configurator interrupts.
    Generation Information : 
        Product Revision  :  MPLAB(c) Code Configurator - 4.35
        Device            :  PIC32MM0064GPL036
    The generated drivers are tested against the following:
        Compiler          :  XC32 1.43
        MPLAB             :  MPLAB X 3.61

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/


/**
    Section: Includes
*/
#include <xc.h>
#include "pin_manager.h"
#include "mcc.h"

/**
    void PIN_MANAGER_Initialize(void)
*/
void PIN_MANAGER_Initialize(void)
{
    /****************************************************************************
     * Setting the Output Latch SFR(s)
     ***************************************************************************/
    LATA = 0x0000;
#if defined BOARD1_MOTORDRIVER
    LATB = 0x4010;
    LATC = 0x0004;
#elif defined BOARD2_COMBINATION
    LATB = 0x4400;
    LATC = 0x0000;
#endif
    /****************************************************************************
     * Setting the GPIO Direction SFR(s)
     ***************************************************************************/
#if defined BOARD1_MOTORDRIVER
    TRISA = 0x000B;
    TRISB = 0xF00F;
#elif defined BOARD2_COMBINATION
    TRISA = 0x000F;
    TRISB = 0xBD6F;		//	U2TX set to input	11i 10i 9o 8i
#else
#error
#endif
    TRISC = 0x0003;

    /****************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     ***************************************************************************/
    CNPDA = 0x0000;
    CNPDB = 0x0000;
    CNPDC = 0x0000;
    CNPUA = 0x0000;
#if defined BOARD1_MOTORDRIVER
    CNPUB = 0x4000;	//	RB14
#elif defined BOARD2_COMBINATION
    CNPUB = 0x0800;	//	RB11
#else
#error
#endif
    CNPUC = 0x0000;
    /****************************************************************************
     * Setting the Open Drain SFR(s)
     ***************************************************************************/
    ODCA = 0x0000;
    ODCB = 0x0000;
    ODCC = 0x0000;

    /****************************************************************************
     * Setting the Analog/Digital Configuration SFR(s)
     ***************************************************************************/
#if defined BOARD1_MOTORDRIVER
    ANSELA = 0x0007;
    ANSELB = 0x300C;
#elif defined BOARD2_COMBINATION
    ANSELA = 0x000F;
    ANSELB = 0x300F;	//0xB00F for AD
#endif
    ANSELC = 0x0003;

    /****************************************************************************
     * Set the PPS
     ***************************************************************************/
    SYSTEM_RegUnlock(); // unlock PPS
    RPCONbits.IOLOCK = 0;

#if defined BOARD1_MOTORDRIVER
    RPOR1bits.RP5R = 0x0001;   //RB4->UART2:U2TX;
    RPINR9bits.U2RXR = 4;	   //RP4=RA3->UART2:U2RX;
    RPOR1bits.RP6R = 0x0006;   //RA4->SCCP2:OCM2;
    RPOR1bits.RP8R = 0x0003;   //RB9->SPI2:SDO2;
    RPOR4bits.RP20R = 0x0007;  //RA9->SCCP3:OCM3;
#elif defined BOARD2_COMBINATION
//    RPINR9bits.U2RXR = 18;     //RP18=RB11->UART2:U2RX;
//    RPOR4bits.RP17R = 0x0001;  //RP17=RB10->UART2:U2TX;
    RPINR9bits.U2RXR = 17;     //RP17=RB10->UART2:U2RX;
    RPOR4bits.RP18R = 0x0001;  //RP18=RB11->UART2:U2TX;
    RPOR1bits.RP5R = 0x0007;   //RB4->SCCP3:OCM3;
    RPOR1bits.RP6R = 0x0007;   //RA4->SCCP3:OCM3;
    RPOR4bits.RP19R = 0x0003;  //RC9->SPI2:SDO2;
    RPOR4bits.RP20R = 0x0006;  //RA9->SCCP2:OCM2;
    RPOR2bits.RP11R = 0x0007;  //RB7->SCCP3:OCM3;
#else
#error
#endif

#if defined BOARD1_MOTORDRIVER
    RPCONbits.IOLOCK = 1; // lock   PPS
#elif defined BOARD2_COMBINATION
	//	BOARD2 need to change PPS to change PWM out pin.
#else
#error
#endif	
    SYSTEM_RegLock(); 
}
