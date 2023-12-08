#include "fixed.h"
#include "command.h"
#include "control.h"
#include "boardType.h"
#include "uart.h"
#include "nvm.h"

#ifdef WROOM
#error This is a source file for PIC only. 
#endif
void commandUartInit(){
	UARTC_Initialize();
	/*	10 = Interrupt flag bit is asserted while receive buffer is 3/4 or more full (i.e., has 6 or more data characters)
		01 = Interrupt flag bit is asserted while receive buffer is 1/2 or more full (i.e., has 4 or more data characters)
		00 = Interrupt flag bit is asserted while receive buffer is not empty (i.e., has at least 1 data character)	*/
	UCSTAbits.URXISEL = 2;
	IEC_UCRXIE = 1;	// Enable UARTC receive interrupt.
	CLEAR_IFS_UCRXIF;

#ifdef PIC32MM
	//	timer to start TXC after receive command header
	//	2M baud/10bit = 200kBps= 5us/byte. Wait 5 bytes = 25us = 600/24MHz
    //  PR1 = (24MHz / baudrate) * 5 bytes 
    PR1 = (24*1000*1000 / PNVDATA->baudrate[0]) * 5;    	//PR1 = 600; //	for 2MBPS, 25us
#elif defined PIC32MK_MCJ
    //  sysclk = 120MHz, BRGH=1
    //  UxBRG = ((CLKSEL Frequency / (4 * Desired Baud Rate)) ? 1)
    //U2BRG = (120 / (4 * 3)) - 1;
    //int U2BRGbefore = U2BRG;
    //U2BRG = (120*1000*1000 / (4*PNVDATA->baudrate[0])) - 1;
    //printf("U2BRG: %d -> %d Baudrate; %d\n", U2BRGbefore, U2BRG, (int)PNVDATA->baudrate[0]);
    //PR1 = (60*1000*1000 / PNVDATA->baudrate[0]) * 5; 
#else
#error
#endif
}


static volatile bool bRunExecCommand=false;
//	handler for TMR1 timer for TX
#ifdef PIC32MM
void __attribute__ ((vector(_TIMER_1_VECTOR), interrupt(IPL3AUTO))) TMR1_ISR()
#elif defined PIC32MK_MCJ
void _TIMER_1_Handler()
#endif
{
    PIC_LOGI("RC%d L%d=", retPacket.commandId, retLen);
    //PIC_LOGI("%02x %02x", (int)command.bytes[1], (int)command.bytes[2]);
    returnCommand[retPacket.commandId]();
    //	stop timer interrupt
    IEC0bits.T1IE = false;
    //	start TX
#ifdef PC32MM
#elif defined PIC32MK_MCJ
    ODCGCLR = 0x200; /* Open Drain Disable for TX*/
#endif
    UCSTAbits.UTXEN = 1;	//	enable TX
    UCSTAbits.UTXISEL = 2;	//	10 = Interrupt is generated and asserted while the transmit buffer is empty
    IEC_UCTXIE = 1;         //	enable UART's interrupt
    IFS0bits.T1IF = false;
}

//  Handler for TX interrupt
#ifdef PC32MM
//	Note: "IPL2" below must fit to "IPC_UCTXIP = 2" in interrupt_manager.c;
void __attribute__ ((vector(_UARTC_TX_VECTOR), interrupt(IPL2AUTO))) _UARTC_TX_HANDLER(void){	
#elif defined PIC32MK_MCJ
void _UARTC_TX_Handler (void){
#endif
	//	Send
	while (retCur < retLen && !UCSTAbits.UTXBF){
		UCTXREG = retPacket.bytes[retCur];
		retCur ++;
	}
	//	StopTX
	if (retCur == retLen){
		UCSTAbits.UTXISEL = 1;		//	01 = Interrupt is generated and asserted when all characters have been transmitted
		if (UCSTAbits.TRMT){		//	TX completed
			IEC_UCTXIE = 0;	//	disable interrupt
#ifdef PC32MM
#elif defined PIC32MK_MCJ
            ODCGSET = 0x200; /* Open Drain Enable for TX*/
#else
#error
#endif
			UCSTAbits.UTXEN = 0;	//	disable UCTX
		}
	}
	CLEAR_IFS_UCTXIF;
}
//	handler for rx interrupt
#ifdef PC32MM
//	Note: "IPL2" below must fit to "IPC_UCTXIP = 2" in interrupt_manager.c;
void __attribute__ ((vector(_UARTC_TX_VECTOR), interrupt(IPL2AUTO))) _UARTC_TX_HANDLER(void){	
//	Note: "IPL4" below must fit to "IPC5bits.UCRXIP = 4" in interrupt_manager.c;
void __attribute__ ((vector(_UARTC_RX_VECTOR), interrupt(IPL4AUTO))) _UARTC_RX_HANDLER(void){
#elif defined PIC32MK_MCJ
void _UARTC_RX_Handler (void){
#endif
	union CommandHeader head;
	static bool bRead;
	int i;
	for(i=0; i<6; ++i){
        if (cmdCur == 0){
	        head.header = UCRXREG;
			//	Skip spacing (make time for return packet), invalid value (They may come after reset.) and invalid command
            if (head.header == 0 || head.header >= (CI_NCOMMAND<<BORADIDBITS)) continue;
			//	In case of valid command ID, get packet length
            cmdLen = cmdPacketLens[head.boardId][head.commandId];
            bRead = false;
			if (head.boardId == boardId){
				bRead = true;
				command.header = head.header;
                //printf("H%x\n", command.header);
				retLen = retPacketLen[command.commandId];
				if (retLen) {	//	start to return.
					//	Prepare to return
					retPacket.header = command.header;
					retCur = 0;
					//	Start TMR1 to enable TX after some delay.
					IFS0bits.T1IF = false;
					IEC0bits.T1IE = true;
					TMR1 = 0;	//	call timer as soon as this task is ended.
				}
            }
            if (head.commandId == CI_SET_CMDLEN){
				bRead = true;
				command.header = head.header;
                //printf("SCL%d len=%d\n", head.boardId, cmdLen);
			}
        }else if (bRead){
			command.bytes[cmdCur] = UCRXREG;
		}else{
			head.header = UCRXREG;
		}
		if (cmdCur == cmdLen-1){
            if (bRead){
				bRunExecCommand = true;	//	exec command in main thread.
            }
            cmdCur = 0;
        } else {
			cmdCur ++;
		}
    }
	CLEAR_IFS_UCRXIF;
}

bool uartExecCommand(){
	if (bRunExecCommand){
		bRunExecCommand = false;
        execCommand[command.commandId]();
		PIC_LOGI("H%x Ex%d\r\n", (int)command.header, (int)command.commandId);
		return true;
	}else{
		return false;
	}
}
