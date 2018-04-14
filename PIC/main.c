/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : v1.45
        Device            :  PIC32MM0064GPL036
    The generated drivers are tested against the following:
        Compiler          :  XC32 1.43
        MPLAB             :  MPLAB X 3.61
*/

/*
 * - 1kHz timer interrupt to call controlLoop()
 * - main thread works for serial communication.
 * - PWM by SDO is not yet implemented.
*/

#include "env.h"
#include "decimal.h"
#include "mcc_generated_files/mcc.h"
#include "control.h"
#include "command.h"
#include <stdio.h>

void puts1(const char* s){
    while(*s){
        UART1_Write(*s);
        s++;
    }
}
void monitor();
void parseUart();
/*
                         Main application
 */
extern int timerRestTime;
int main(void)
{
    int i = 0;
    SYSTEM_Initialize();
#ifndef MODULETEST
    U2TXREG = 'S';
	UART2_Write('t');
    printf("art");
    UART2_Write('.');
    UART2_Write('\r');
    UART2_Write('\n');

#if 0	//	uart test
	U1STAbits.UTXEN = 1;
	while(1){
		while(!U1STAbits.UTXBF){
			U1TXREG = 'A';
		}
	}
#endif
    controlInit();
	commandInit();
	while(1){
		monitor();
#ifndef PICUARTINT
		uartLoop();
#endif
		monOut();
#if 0
		i++;
		if (i>10000){
			i = 0;
			printf("T:%d\r\n", timerRestTime);
		}
#endif
	}

#else
    puts1("Start.\n");
#if 1   //  test for interpolation
    controlInit();
    controlSetMode(CM_INTERPOLATE);
    {
        int ip = 0;
        for(i=0; i<60; ++i){
            int j;
#if 1
            while(targetsWriteAvail() > 0){
                short tgs[NMOTOR];
				for(j=0; j<NMOTOR; ++j) tgs[j] = (ip+1) * SDEC_ONE / (3+j);
                targetsAdd(tgs, 10);
                if (ip < 1) ip++;
            }
#endif
            for(j=0; j<3000; ++j);
			printMotorControl();
        }
    }
#endif

#if 0   //  test for motor velocity
    for(i=0; i<200; ++i){
        controlLoop();
        printMotorState();
    }
#endif
#if 0   //  test for motor angle read
    for(i=0; i<200; ++i){
        updateMotorState();
        printMotorState();
    }
#endif
#if 0   //  test for atan2S
    atan2FixedTest();
#endif

#endif
    // When using interrupts, you need to set the Global Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalDisable();

    while (1)
    {
        // Add your application code
    }
}
/**
 End of File
*/