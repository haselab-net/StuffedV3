/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    mcc.c

  @Summary:
    This is the mcc.c file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
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
#include "../boardType.h"

// Configuration bits: selected in the GUI

// FDEVOPT
#pragma config SOSCHP = OFF    // Secondary Oscillator High Power Enable bit->SOSC oprerates in normal power mode.

// FICD
#pragma config JTAGEN = OFF    // JTAG Enable bit->JTAG is disabled
#if defined BOARD1_MOTORDRIVER
#pragma config ICS = PGx1    // ICE/ICD Communication Channel Selection bits->Communicate on PGEC1/PGED1
#elif defined BOARD2_COMBINATION || defined BOARD3_SEPARATE || defined BOARD4
#pragma config ICS = PGx3    // ICE/ICD Communication Channel Selection bits->Communicate on PGEC3/PGED3
#else
#error
#endif


// FPOR
#pragma config BOREN = BOR3    // Brown-out Reset Enable bits->Brown-out Reset enabled in hardware; SBOREN bit disabled
#pragma config RETVR = OFF    // Retention Voltage Regulator Enable bit->Retention regulator is disabled
#pragma config LPBOREN = ON    // Low Power Brown-out Enable bit->Low power BOR is enabled, when main BOR is disabled

// FWDT
#pragma config SWDTPS = PS1048576    // Sleep Mode Watchdog Timer Postscale Selection bits->1:1048576
#pragma config FWDTWINSZ = PS25_0    // Watchdog Timer Window Size bits->Watchdog timer window size is 25%
#pragma config WINDIS = OFF    // Windowed Watchdog Timer Disable bit->Watchdog timer is in non-window mode
#pragma config RWDTPS = PS1048576    // Run Mode Watchdog Timer Postscale Selection bits->1:1048576
#pragma config RCLKSEL = LPRC    // Run Mode Watchdog Timer Clock Source Selection bits->Clock source is LPRC (same as for sleep mode)
#pragma config FWDTEN = OFF    // Watchdog Timer Enable bit->WDT is disabled

// FOSCSEL
#pragma config FNOSC = FRCDIV    // Oscillator Selection bits->Fast RC oscillator (FRC) with divide-by-N
#pragma config PLLSRC = FRC    // System PLL Input Clock Selection bit->FRC oscillator is selected as PLL reference input on device reset
#pragma config SOSCEN = OFF    // Secondary Oscillator Enable bit->Secondary oscillator (SOSC) is disabled
#pragma config IESO = OFF    // Two Speed Startup Enable bit->Two speed startup is disabled
#pragma config POSCMOD = OFF    // Primary Oscillator Selection bit->Primary oscillator is disabled

									//	changed by hase
#pragma config OSCIOFNC = OFF    // Bug on MCC, must overwrite by hand to use RA3 as IO pin
// System Clock on CLKO Pin Enable bit->System clock is connected to CLKO/OSC2 pin

#pragma config SOSCSEL = ON    // Secondary Oscillator External Clock Enable bit->External clock is connected to SOSCO pin (RA4 and RB4 are controlled by I/O port registers)
#pragma config FCKSM = CSECMD    // Clock Switching and Fail-Safe Clock Monitor Enable bits->Clock switching is enabled; Fail-safe clock monitor is disabled

// FSEC
#pragma config CP = OFF    // Code Protection Enable bit->Code protection is disabled

#include "mcc.h"

void SYSTEM_Initialize(void)
{
    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
    INTERRUPT_Initialize();
    CORETIMER_Initialize();
    UART2_Initialize();
    SCCP3_COMPARE_Initialize();
    UART1_Initialize();
#ifndef __MPLAB_DEBUGGER_SIMULATOR
    ADC1_Initialize();
#endif
    SCCP2_COMPARE_Initialize();
    TMR1_Initialize();
    MCCP1_COMPARE_Initialize();
    INTERRUPT_GlobalEnable();
}


void OSCILLATOR_Initialize(void)
{
    SYSTEM_RegUnlock();
    // TUN Center frequency; 
    OSCTUN = 0x0;
    // PLLODIV 1:1; PLLMULT 3x; PLLICLK FRC; 
    SPLLCON = 0x10080;
    // SBOREN disabled; VREGS disabled; RETEN disabled; 
    PWRCON = PWRCON | 0x0;
    //Clear NOSC,CLKLOCK and OSWEN bits
    OSCCONCLR = _OSCCON_NOSC_MASK | _OSCCON_CLKLOCK_MASK | _OSCCON_OSWEN_MASK;
    // CF No Clock Failure; FRCDIV FRC/1; SLPEN Device will enter Idle mode when a WAIT instruction is issued; NOSC SPLL; SOSCEN disabled; CLKLOCK Clock and PLL selections are not locked and may be modified; OSWEN Oscillator switch initiate; 
    OSCCON = (0x100 | _OSCCON_OSWEN_MASK);
    SYSTEM_RegLock();
    // wait for switch   
    while(OSCCONbits.OSWEN == 1); 
    // ON disabled; DIVSWEN disabled; RSLP disabled; ROSEL SYSCLK; OE disabled; SIDL disabled; RODIV 0; 
    REFO1CON = REFO1CON | 0x0;
    while(!REFO1CONbits.ACTIVE & REFO1CONbits.ON);
    // ROTRIM 0; 
    REFO1TRIM = REFO1TRIM | 0x0;
}

/**
 End of File
*/