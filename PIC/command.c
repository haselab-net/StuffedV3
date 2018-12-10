#include "fixed.h"
#include "command.h"
#include "control.h"
#include "boardType.h"
#include <string.h>

unsigned char boardId = BOARD_ID;

CommandPacket command;
int cmdCur;
int cmdLen;
int retLen;

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
    int i;
    static SDEC newPos, diff;
    controlSetMode(CM_DIRECT);
    for(i=0; i<NMOTOR; ++i){
#if 1
        newPos = command.direct.pos[i];
        diff = newPos - L2SDEC(motorTarget.pos[i]);
        motorTarget.pos[i] += S2LDEC(diff);
#else
        motorTarget.pos[i] = S2LDEC(command.direct.pos[i]);
#endif
        motorTarget.vel[i] = S2LDEC(command.direct.vel[i]);
    }
}
void ecInterpolate(){
    controlSetMode(CM_INTERPOLATE);
	targetsAddOrUpdate(command.interpolate.pos, command.interpolate.period, command.interpolate.count);
}
void ecForceControl(){
    controlSetMode(CM_FORCE_CONTROL);
	targetsForceControlAddOrUpdate(command.forceControl.pos , command.forceControl.Jacob, command.forceControl.period, command.forceControl.count);
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
void ecResetSensor(){
    int i;
    if (command.resetSensor.flags & RSF_MOTOR){
        for(i=0; i<NMOTOR; ++i){
            motorState.pos[i] = motorState.pos[i] % LDEC_ONE;
            motorState.vel[i] = 0;
            motorTarget.pos[i] = motorTarget.pos[i] % LDEC_ONE;
        }
    }
    if (command.resetSensor.flags & RSF_FORCE){
        for(i=0; i<NFORCE; ++i){
            forceOffset[i] = getForceRaw(i);
        }
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
    controlSetMode(CM_FORCE_CONTROL);
	returnInterpolateParam();
}

ExecCommand* execCommand[CI_NCOMMAND] = {
	ecNop,
	ecNop,		//	board info
	ecSetCmdLen,
	ecNop,
	ecDirect,
    ecInterpolate,	//	interpolate
	ecForceControl,	//	force control
    ecPdParam,
    ecTorqueLimit,
    ecResetSensor,
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
    rcNop,	//	resetSensor
};

#ifdef WROOM
void ExecCmd(void* cmd, int len){
	assert(sizeof(command) == len);
	memcpy(&command, cmd, len);
	execCommand[command.commandId]();
}
void ExecRet(void* ret, int len){
	retPacket.header = command.header;
	returnCommand[retPacket.commandId]();
	assert(sizeof(retPacket) == len);
	memcpy(ret, &retPacket, len);
}
#endif

void commandInit(){
	int i, c;
	for(i=0; i<MAXBOARDID+1; ++i){
		for(c=0; c<CI_NCOMMAND; ++c){
			cmdPacketLens[i][c] = cmdPacketLen[c];
		}
	}
}
