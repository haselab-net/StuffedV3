/**
  System Interrupts Generated Driver File 

  @Company:
    Microchip Technology Inc.

  @File Name:
    interrupt_manager.h

  @Summary:
    This is the generated driver implementation file for setting up the
    interrupts using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This source file provides implementations for PIC24 / dsPIC33 / PIC32MM MCUs interrupts.
    Generation Information : 
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : v1.45
        Device            :  PIC32MM0064GPL036
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
    Section: Includes
*/
#include <xc.h>
#include "../uart.h"

/**
    void INTERRUPT_Initialize (void)
*/
void INTERRUPT_Initialize (void)
{
    // Enable Multi Vector Configuration
    INTCONbits.MVEC = 1;
    
    //    SPITXI: SPI 2 Transmission
    IPC9bits.SPI2TXIP = 6;    //    Priority: 6
    IPC9bits.SPI2TXIS = 0;    //    Sub Priority: 0

    //	UART to commucate with the main board
	IPC_UCRXIP = 4;	//	receive first
	IPC_UCRXIS = 0; 
	IPC_UCTXIP = 2;	//	the send
	IPC_UCTXIS = 0;
		
	//    CTI: Core Timer
    IPC0bits.CTIP = 1;
    IPC0bits.CTIS = 0;

    //    TI: Timer 1
    IPC2bits.T1IP = 3;
    IPC2bits.T1IS = 0;
}
