#ifndef _CONTROL_H
#define _CONTROL_H
#include "env.h"
#include "decimal.h"
#include "command.h"

#ifdef __XC32
#include "mcc_generated_files/mcc.h"
#endif


//  data buffer
struct MotorState{
    LDEC pos[NMOTOR];
    LDEC vel[NMOTOR];
};
extern struct MotorState motorTarget, motorState;
extern SDEC forceControlJK[NFORCE][NMOTOR];
#define NAXIS	4	//	NAXIS=NMOTOR+NFORCE/2
extern SDEC mcos[NAXIS], msin[NAXIS];

struct PdParam{
    SDEC k[NMOTOR];
    SDEC b[NMOTOR];
};
extern struct PdParam pdParam;

struct TorqueLimit{
    SDEC min[NMOTOR];
    SDEC max[NMOTOR];
};
extern struct TorqueLimit torqueLimit;

struct Target{
	short period;	//	update period for interpolation
	SDEC pos[NMOTOR];
	SDEC JK[NFORCE][NMOTOR];
};
struct Targets{
	short tick;		//	current tick count
	volatile char read;         //	interpolation works between "pos[read]" and "pos[read+1]".
	volatile char write;		//	cursor to add new data. pos[write] = newdata.
	struct Target buf[NTARGET];
};
extern struct Targets targets;

enum ControlMode{
    CM_DIRECT,
    CM_INTERPOLATE,
    CM_FORCE_CONTROL,
};
extern enum ControlMode controlMode;

void targetsInit();
void targetsAdd(short* pos, short period);
void targetsForceControlAdd(SDEC* pos, SDEC JK[NFORCE][NMOTOR] ,short period);
void targetsWrite();
int targetsWriteAvail();
int targetsReadAvail();

void controlInit();
void controlSetMode(enum ControlMode m);
void controlLoop();

inline SDEC getForce(int ch){
	if (ch == 0) return mcos[3];
	if (ch == 1) return msin[3];
}

extern int timeOutCount;
extern int timerRestTime;
extern uint32_t coretimerCompare;

#endif
