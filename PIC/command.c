#include "decimal.h"
#include "command.h"
#include "control.h"
#include "mcc_generated_files/uart1.h"
#include "uart.h"
#include "boardType.h"

unsigned char boardId = BOARD_ID;

CommandPacket command;
int cmdCur;
int cmdLen;
int retLen;
static volatile bool bRunExecCommand=false;

//	command packet length for all boards
unsigned char cmdPacketLens[MAXBOARDID+1][CI_NCOMMAND];

void ecNop(){
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
	targetsAddOrUpdate(command.interpolate.pos, command.interpolate.period, command.interpolate.count);
}
void ecForceControl(){
    controlSetMode(CM_FORCE_CONTROL);
	targetsForceControlAddOrUpdate(command.forceControl.pos , command.forceControl.JK, command.forceControl.period, command.forceControl.count);
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
void rcNop(){
}
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
inline void returnInterpolateParam(){
    int i;	
    for(i=0; i<NMOTOR; ++i){
        retPacket.interpolate.pos[i] = L2SDEC(motorState.pos[i]);
    }
    retPacket.interpolate.countOfRead = targets.countOfRead;
	retPacket.interpolate.tick = targets.tick;
}
void rcInterpolate(){
    controlSetMode(CM_INTERPOLATE);
	returnInterpolateParam();
}
void rcForceControl(){
    int i;
    controlSetMode(CM_FORCE_CONTROL);
	returnInterpolateParam();
}

typedef void ExecCommand();
ExecCommand* execCommand[CI_NCOMMAND] = {
	ecNop,
	ecNop,		//	board info
	ecSetCmdLen,
	ecNop,
	ecDirect,
    ecInterpolate,	//	interpolate
	ecForceControl,	//	force control
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
    rcInterpolate,
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
	UCSTAbits.URXISEL = 2;
	IEC_UCRXIE = 1;	// Enable uart1 receive interrupt.

	//	timer to start TX1 after receive command header
		//	2M baud/10bit = 200kBps= 5us/byte. 3600/24M=150us
		//PR1 = 3600;		//	150us
		PR1 = 600;			//	25us
	}


uint32_t timeRetCmd, timeTx;

//	handler for TMR1 timer for TX
volatile bool bRunReturnCommand = false;
void __attribute__ ((vector(_TIMER_1_VECTOR), interrupt(IPL3AUTO))) TMR1_ISR()
{
	if (bRunReturnCommand){	//	call from recv
		bRunReturnCommand = false;
		LOGI("RC%d len%d ", retPacket.commandId, retLen);
		returnCommand[retPacket.commandId]();
		timeRetCmd = TMR1;
		IFS0bits.T1IF = false;
	}else{
		//	stop timer interrupt
		IEC0bits.T1IE = 0;
		//	start TX
		UCSTAbits.UTXEN = 1;	//	enable TX
		UCSTAbits.UTXISEL = 2;	//	10 = Interrupt is generated and asserted while the transmit buffer is empty
		IEC_UCTXIE = 1;	//	enable interrupt
		timeTx = TMR1 + PR1;
	}
	IFS0CLR= 1 << _IFS0_T1IF_POSITION;
}

//  Handler for TX interrupt
//	Note: "IPL2" below must fit to "IPC_UCTXIP = 2" in interrupt_manager.c;
void __attribute__ ((vector(_UARTC_TX_VECTOR), interrupt(IPL2AUTO))) _UARTC_TX_HANDLER(void){	
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
			UCSTAbits.UTXEN = 0;	//	disable UCTX
		}
	}
	CLEAR_IFS_UCTXIF;
}
//	handler for rx interrupt
//	Note: "IPL4" below must fit to "IPC5bits.UCRXIP = 4" in interrupt_manager.c;
void __attribute__ ((vector(_UART1_RX_VECTOR), interrupt(IPL4AUTO))) _UART1_RX_HANDLER(void){
	int i;
	union CommandHeader head;
	static bool bRead;
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
				retLen = retPacketLen[command.commandId];
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
		LOGI("H%x Ex%d\r\n", (int)command.header, (int)command.commandId);
		return true;
	}else{
		return false;
	}
}



