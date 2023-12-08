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
#include "fixed.h"
#ifdef PIC32MM
#include "mcc_generated_files/mcc.h"
#elif defined PIC32MK_MCJ
#include "definitions.h"
#include "initMk.h"
#else
 #error
#endif
#include "control.h"
#include "command.h"
#include "uart.h"
#include "nvm.h"
#include <stdio.h>
#include <string.h>

void monitor();
bool monOut();
void commandUartInit();

/*
                         Main application
 */
extern int timerRestTime;
int main(void)
{
#ifdef PIC32MM    
    SYSTEM_Initialize();
#elif defined PIC32MK_MCJ
    initMk();
#else
#error
#endif
    UMTXREG = 'S';
    printf("tart.\r\n");
    boardId = PNVDATA->boardId;
    if (boardId > 7) boardId = 7;
    printf("Borad ID:%d Model:%d nTargets:%d nMotor:%d nCurrent:%d nForce:%d\r\n", boardId, MODEL_NUMBER, NTARGET, NMOTOR, NCURRENT, NFORCE);
    controlInit();
	commandInit();
	commandUartInit();
#if 0
    printf("UMRXREG=%x ", UMRXREG);
    printf("UMSTA=%x\r\n", UMSTA);
    while(1){
        if (UMSTAbits.URXDA){
            printf("UMSTA=%x, RX=%x\r\n", UMSTA, UMRXREG);            
        }
    }
#endif
	while(1){
		if (!uartExecCommand()){
#ifdef PIC32MM
			uint32_t now = _CP0_GET_COUNT();
			uint32_t cmp = _CP0_GET_COMPARE();
			int diff = cmp - now;
			if (diff < -3000){	//	delay 1ms 
				coretimerCompare = now + 3000;
				_CP0_SET_COMPARE(coretimerCompare);
				//printf("RO\r\n");
			}
#endif
			if (UMSTAbits.TRMT){
				monitor();
			}else{
				monOut();
			}
		}
	}
}
/**
 End of File
*/