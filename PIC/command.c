#include "decimal.h"
#include "command.h"
#include "control.h"
#include "mcc_generated_files/uart1.h"

unsigned char boardId = 0;
CommandPacket command;
int cmdCur;
int cmdLen;

//	command packet length for all boards
unsigned char cmdPacketLens[MAXBOARDID+1][CI_NCOMMAND];
void commandInit(){
	int i, c;
	for(i=0; i<MAXBOARDID+1; ++i){
		for(c=0; c<CI_NCOMMAND; ++c){
			cmdPacketLens[i][c] = cmdPacketLen[c];
		}
	}
#ifdef PICUARTINT
	U1STAbits.URXISEL = 0;	// 00 = Interrupt flag bit is asserted while receive buffer is not empty (i.e., has at least 1 data character)	
	IEC0bits.U1RXIE = 1;	// Enable uart1 receive interrupt.
#endif
}

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

void uartSendRet(){
	while (retCur < retLen && !U1STAbits.UTXBF){
		U1TXREG = retPacket.bytes[retCur];
		retCur ++;
	}
	if (retCur == retLen && U1STAbits.TRMT){	//	TX completed and disable
		U1STAbits.UTXEN = 0;
	}
}

#ifdef PICUARTINT

//  handler for tx interrupt
//	Note: "IPL3" below must fit to "IPC5bits.U1TXIP = 3" in interrupt_manager.c;
void __attribute__ ((vector(_UART1_TX_VECTOR), interrupt(IPL3SOFT))) _UART1_TX_HANDLER(void){	
	while (retCur < retLen && !U1STAbits.UTXBF){
		U1TXREG = retPacket.bytes[retCur];
		retCur ++;
	}
	if (retCur == retLen){
		U1STAbits.UTXISEL = 1;	//	01 = Interrupt is generated and asserted when all characters have been transmitted
		if (U1STAbits.TRMT){	//	TX completed and disable
			IEC0bits.U1TXIE = 0;	//	disable interrupt
			U1STAbits.UTXEN = 0;	//	disbble U1X
		}
	}
	IFS0CLR= 1 << _IFS0_U1TXIF_POSITION;	//	clear interrupt flag
}

//	handler for rx interrupt
void onReceive();
//	Note: "IPL4" below must fit to "IPC5bits.U1RXIP = 4" in interrupt_manager.c;
void __attribute__ ((vector(_UART1_RX_VECTOR), interrupt(IPL4SOFT))) _UART1_RX_HANDLER(void){
	onReceive();
	IFS0CLR = 1 << _IFS0_U1RXIF_POSITION;	//	clear interrupt flag
}
void onReceive(){
    while (U1STAbits.URXDA == 1){
        command.bytes[cmdCur] = U1RXREG;
        if (cmdCur == 0){
			//	skip invalid value. They can arrive after reest.
            if (command.bytes[0] == 0 || command.bytes[0] == 0xFF) continue;
			//	skip invalid command 
			if (command.commandId >= CI_NCOMMAND) continue;
			//	In case of valid command ID, get packet length
            cmdLen = cmdPacketLens[command.boardId][command.commandId];
#ifdef DEBUG
			printf("%02xL%d", command.header, cmdLen);
#endif
			//	start to send return packet.
            if (command.boardId == boardId){
				retPacket.header = command.header;
                returnCommand[retPacket.commandId]();
				retCur = 0;
				retLen = retPacketLen[retPacket.commandId];
				if (retLen) {	//	Enable and start TX
					U1STAbits.UTXISEL = 2;	//	10 = Interrupt is generated and asserted while the transmit buffer is empty
					U1STAbits.UTXEN = 1;	//	enable TX
					IEC0bits.U1TXIE = 1;	//	enable interrupt
				}
            }
        }
#ifdef DEBUG
		//	Too heavy for 2M baud UART
		//		printf(" %02x", (unsigned int)command.bytes[cmdCur]);
#endif
		if (cmdCur == cmdLen-1){
            if (command.boardId == boardId || command.commandId == CI_SET_CMDLEN){
				printf("Ex%d\r\n", command.commandId);
                execCommand[command.commandId]();
            }
#ifdef DEBUG
			else{
				printf("\r\n");
			}
#endif
            cmdCur = 0;
        } else {
			cmdCur ++;
		}
    }
}
#else
void uartLoop(){
    while (U1STAbits.URXDA == 1){
        command.bytes[cmdCur] = U1RXREG;
        if (cmdCur == 0){
            if (command.bytes[0] == 0) break;		//	After reset
            if (command.bytes[0] == 0xFF) break;	//	After reset
			if (command.commandId >= CI_NCOMMAND) break; // invalid command
            cmdLen = cmdPacketLens[command.boardId][command.commandId];
#ifdef DEBUG
			printf("%02xL%d", command.header, cmdLen);
#endif
			//	start to send return packet.
            if (command.boardId == boardId){
				retPacket.header = command.header;
                returnCommand[retPacket.commandId]();
				retCur = 0;
				retLen = retPacketLen[retPacket.commandId];
				if (retLen) {	//	Enable and start TX
					U1STAbits.UTXEN = 1;
					uartSendRet();
				}
            }
        }
#ifdef DEBUG
		//	Too heavy for 2M baud UART
		//		printf(" %02x", (unsigned int)command.bytes[cmdCur]);
#endif
		if (cmdCur == cmdLen-1){
            if (command.boardId == boardId || command.commandId == CI_SET_CMDLEN){
				printf("Ex%d\r\n", command.commandId);
                execCommand[command.commandId]();
            }
#ifdef DEBUG
			else{
				printf("\r\n");
			}
#endif
            cmdCur = 0;
        } else {
			cmdCur ++;
		}
    }
	uartSendRet();
}
#endif