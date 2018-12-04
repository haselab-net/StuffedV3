#ifndef _CONTROL_H
#define _CONTROL_H
//	This file works for both PIC and WROOM

#include "env.h"
#include "fixed.h"
#include "command.h"
#ifdef __XC32
#include "mcc_generated_files/mcc.h"
#endif

//	device depended functions
void readADC();						//	read adc and set it to mcos and msin
void setPwm(int ch, SDEC ratio);	//	set pwm of motor

//  data buffer
struct MotorState{
    LDEC pos[NMOTOR];
    LDEC vel[NMOTOR];
};
extern struct MotorState motorTarget, motorState;
extern SDEC forceControlJK[NFORCE][NMOTOR];
#define NAXIS	(NMOTOR+NFORCE/2)	//	NAXIS=NMOTOR+NFORCE/2
extern SDEC mcos[NAXIS], msin[NAXIS];
extern const SDEC mcosOffset[NAXIS];
extern const SDEC msinOffset[NAXIS];

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
	short period;	//	period to reach this target.
	SDEC pos[NMOTOR];
	SDEC Jacob[NFORCE][NMOTOR];
};
struct Targets{
	unsigned short tick;		//	current tick count
	volatile unsigned char countOfRead;	//	couner value of buf[read]
	volatile char read;         //	interpolation works between "pos[read]" and "pos[read+1]".
	volatile char write;		//	cursor to add new data. pos[write] = newdata.
	volatile struct Target buf[NTARGET];
};
extern struct Targets targets;

enum ControlMode{
    CM_DIRECT,
    CM_INTERPOLATE,
    CM_FORCE_CONTROL,
};
extern enum ControlMode controlMode;

void targetsInit();
void targetsAddOrUpdate(short* pos, short period, unsigned char count);
void targetsForceControlAddOrUpdate(SDEC* pos, SDEC JK[NFORCE][NMOTOR] ,short period, unsigned char count);
void targetsWrite();
inline unsigned char targetsWriteAvail(){
	int len = targets.read - targets.write;
	if (len < 0) len += NTARGET;
	return len;
}
inline unsigned char targetsReadAvail(){
	char len = targets.write - targets.read;
	if (len <= 0) len += NTARGET;
	return len;
}
int targetsCountMin();
int targetsCountMax();

void controlInit();
void controlSetMode(enum ControlMode m);
void controlLoop();

extern SDEC forceOffset[NFORCE];

inline SDEC getForceRaw(int ch){
	if (ch == 0) return mcos[3];
	if (ch == 1) return msin[3];
	return 0;
}
inline SDEC getForce(int ch){
	if (ch == 0) return mcos[3] - forceOffset[ch];
	if (ch == 1) return msin[3] - forceOffset[ch];
	return 0;
}

inline short FilterForADC(short prev, short cur){
    const short IIR = 1;
    return (prev*(IIR-1) + cur) / IIR;
}

#ifdef PIC
extern int coretimerRemainTime;
extern uint32_t coretimerCompare;
extern uint32_t controlCount;
#endif

#endif
