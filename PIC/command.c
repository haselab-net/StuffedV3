#include "decimal.h"
#include "command.h"
#include "control.h"
#include "mcc_generated_files/uart1.h"

unsigned char boardId = 2;

CommandPacket command;
int cmdCur;
int cmdLen;
int retLen;
static volatile bool bRunExecCommand=false;

//	command packet length for all boards
unsigned char cmdPacketLens[MAXBOARDID+1][CI_NCOMMAND];


void ecNop(){
}
void ecBoardInfo(){
}
void ecSetCmdLen(){
	int c;
	for(c=0; c<CI_NCOMMAND; ++c){
		cmdPacketLens[command.boardId][c] = command.cmdLen.len[c];
	}
}
void ecDirect(){
    controlSetMode(CM_DIRECT);
    int i;
    for(i=0; i<NMOTOR; ++i){
        motorTarget.pos[i] = S2LDEC(command.direct.pos[i]);
        motorTarget.vel[i] = S2LDEC(command.direct.vel[i]);
    }
}
void ecInterpolate(){
    controlSetMode(CM_INTERPOLATE);
	targetsAdd(command.interpolate.pos, command.interpolate.period);
}
void ecForceControl(){
    controlSetMode(CM_FORCE_CONTROL);
	targetsForceControlAdd(command.forceControl.pos , command.forceControl.JK, command.forceControl.period);
}
void ecPdParam(){
    int i;
    for(i=0; i<NMOTOR; ++i){
        pdParam.k[i] = command.pdParam.k[i];
        pdParam.b[i] = command.pdParam.b[i];
    }
}
void ecTorqueLimit(){
    int i;
    for(i=0; i<NMOTOR; ++i){
        torqueLimit.min[i] = command.torqueLimit.min[i];
        torqueLimit.max[i] = command.torqueLimit.max[i];
    }
}

ReturnPacket retPacket;
int retCur;
int retLen;
void rcBoardInfo(){
	retPacket.boardInfo.modelNumber = MODEL_NUMBER;
	retPacket.boardInfo.nTarget = NTARGET;
	retPacket.boardInfo.nMotor = NMOTOR;
	retPacket.boardInfo.nForce = NFORCE;
}
void rcSensor(){
    int i;
    for(i=0; i<NMOTOR; ++i){
		retPacket.sensor.pos[i] = L2SDEC(motorState.pos[i]);
    }
    for(i=0; i<NFORCE; ++i){
		retPacket.sensor.force[i] = getForce(i);
    }
}
void rcDirect(){
    int i;
    for(i=0; i<NMOTOR; ++i){
        retPacket.direct.pos[i] = L2SDEC(motorState.pos[i]);
        retPacket.direct.vel[i] = L2SDEC(motorState.vel[i]);
    }
}
void rcInterpolate(){
    int i;
    for(i=0; i<NMOTOR; ++i){
        retPacket.interpolate.pos[i] = L2SDEC(motorState.pos[i]);
    }
    retPacket.interpolate.vacancy = targetsWriteAvail();
    retPacket.interpolate.remain = targetsReadAvail();
    retPacket.interpolate.tick = targets.tick;
}
void rcForceControl(){
	rcInterpolate();
}
void rcNop(){
}

typedef void ExecCommand();
ExecCommand* execCommand[CI_NCOMMAND] = {
    ecNop,
	ecBoardInfo,
	ecSetCmdLen,
	ecNop,
	ecDirect,
    ecInterpolate,
	ecForceControl,
    ecPdParam,
    ecTorqueLimit
};
ExecCommand* returnCommand[CI_NCOMMAND] = {
    rcNop,
	rcBoardInfo,
    rcNop,
	rcSensor,
    rcDirect,
    rcInterpolate,
    rcForceControl,
	rcNop,	//	pdParam
    rcNop,	//	torqueLimit
};


void commandInit(){
	int i, c;
	for(i=0; i<MAXBOARDID+1; ++i){
		for(c=0; c<CI_NCOMMAND; ++c){
			cmdPacketLens[i][c] = cmdPacketLen[c];
		}
	}
	/*	10 = Interrupt flag bit is asserted while receive buffer is 3/4 or more full (i.e., has 6 or more data characters)
		01 = Interrupt flag bit is asserted while receive buffer is 1/2 or more full (i.e., has 4 or more data characters)
		00 = Interrupt flag bit is asserted while receive buffer is not empty (i.e., has at least 1 data character)	*/
	U1STAbits.URXISEL = 2;
	IEC0bits.U1RXIE = 1;	// Enable uart1 receive interrupt.

	//	timer to start TX1 after receive command header
		//	2M baud/10bit = 200kBps= 5us/byte. 3600/24M=150us
		//PR1 = 3600;		//	150us
		PR1 = 600;			//	25us
	}


uint32_t timeRetCmd, timeTx;

//	handler for TMR1 timer for TX
volatile bool bRunReturnCommand = false;
void __attribute__ ((vector(_TIMER_1_VECTOR), interrupt(IPL3SOFT))) TMR1_ISR()
{
	if (bRunReturnCommand){	//	call from recv
		bRunReturnCommand = false;
		returnCommand[retPacket.commandId]();
		timeRetCmd = TMR1;
		IFS0bits.T1IF = false;
	}else{
		//	stop timer interrupt
		IEC0bits.T1IE = 0;
		//	start TX
		U1STAbits.UTXEN = 1;	//	enable TX
		U1STAbits.UTXISEL = 2;	//	10 = Interrupt is generated and asserted while the transmit buffer is empty
		IEC0bits.U1TXIE = 1;	//	enable interrupt
		timeTx = TMR1 + PR1;
	}
	IFS0CLR= 1 << _IFS0_T1IF_POSITION;
}

//  Handler for TX interrupt
//	Note: "IPL2" below must fit to "IPC5bits.U1TXIP = 2" in interrupt_manager.c;
void __attribute__ ((vector(_UART1_TX_VECTOR), interrupt(IPL2SOFT))) _UART1_TX_HANDLER(void){	
	//	Send
	while (retCur < retLen && !U1STAbits.UTXBF){
		U1TXREG = retPacket.bytes[retCur];
		retCur ++;
	}
	//	StopTX
	if (retCur == retLen){
		U1STAbits.UTXISEL = 1;		//	01 = Interrupt is generated and asserted when all characters have been transmitted
		if (U1STAbits.TRMT){		//	TX completed
			IEC0bits.U1TXIE = 0;	//	disable interrupt
			U1STAbits.UTXEN = 0;	//	disable U1TX
		}
	}
	IFS0CLR= 1 << _IFS0_U1TXIF_POSITION;	//	clear interrupt flag
}

//	handler for rx interrupt
//	Note: "IPL4" below must fit to "IPC5bits.U1RXIP = 4" in interrupt_manager.c;
void __attribute__ ((vector(_UART1_RX_VECTOR), interrupt(IPL4SOFT))) _UART1_RX_HANDLER(void){
	int i;
	union CommandHeader head;
	static bool bRead;
	for(i=0; i<6; ++i){
        if (cmdCur == 0){
	        head.header = U1RXREG;
			//	Skip spacing (make time for return packet), invalid value (They may come after reset.) and invalid command
            if (head.header == 0 || head.header >= (CI_NCOMMAND<<BORADIDBITS)) continue;
			//	In case of valid command ID, get packet length
            cmdLen = cmdPacketLens[head.boardId][head.commandId];
            bRead = false;
			if (head.boardId == boardId){
				bRead = true;
				command.header = head.header;
				retLen = retPacketLen[command.commandId];
				//printf("retLen%d\r\n", retLen);
				if (retLen) {	//	start to return.
					//	Prepare to return
					retPacket.header = command.header;
					retCur = 0;
					//	Start TMR1 to enable TX after some delay.
					bRunReturnCommand = true;
					IEC0bits.T1IE = true;
					IFS0bits.T1IF = false;
					TMR1 = PR1-1;	//	call timer as soon as this task is ended.
				}
            }
			if (head.commandId == CI_SET_CMDLEN){
				bRead = true;
				command.header = head.header;
			}
        }else if (bRead){
			command.bytes[cmdCur] = U1RXREG;
		}else{
			head.header = U1RXREG;
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
	IFS0CLR = 1 << _IFS0_U1RXIF_POSITION;	//	clear interrupt flag
}

void uartExecCommand(){
	if (bRunExecCommand){
		bRunExecCommand = false;
        execCommand[command.commandId]();
		//printf("H%x Ex%d ", (int)command.header, (int)command.commandId);
	}else{
#if 0
		if (timeTx - timeRetCmd < 5000){
			printf("RC%d W%d\r\n", timeRetCmd, timeTx-timeRetCmd);
			timeTx = timeRetCmd + 10000;
		}
#endif
#if 0
		static int i;
		i++;
		if (i>30000){
			printf("U1STA %8x\r\n", U1STA);
			i = 0;
		}
#endif
	}
}



