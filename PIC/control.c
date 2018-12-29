#include "env.h"
#include "fixed.h"
#include "control.h"
#include <assert.h>

struct MotorState motorTarget, motorState;
SDEC forceControlJK[NFORCE][NMOTOR];
struct PdParam pdParam;
struct TorqueLimit torqueLimit;
struct Targets targets;
enum ControlMode controlMode;
//	 angle
SDEC mcos[NAXIS], msin[NAXIS];
SDEC forceOffset[NFORCE];
SDEC currentSense[NMOTOR];

uint32_t controlCount;

//----------------------------------------------------------------------------
//	Control
//
void updateMotorState(){
    int i;
	readADC();
    for(i=0; i<NMOTOR; ++i){
        LDEC sense, prev, cur, diff;
		if (mcos[i] || msin[i]){
			sense = S2LDEC(atan2SDEC(msin[i], mcos[i]));
			cur = prev = motorState.pos[i];
			diff = sense - GetDecimalL(prev);
			cur += diff;
			if (diff < -LDEC_ONE/2){
				cur += LDEC_ONE;
			}else if (diff > LDEC_ONE/2){
				cur -= LDEC_ONE;
			}
			motorState.pos[i] = cur;
			motorState.vel[i] = motorState.pos[i] - prev;
		}
#if 0
		if (i==0){
			printf("p %f,  s %f, (%d,%d) %d\r\n", LDEC2DBL(motorState.pos[i]), LDEC2DBL(sense), msin[i], mcos[i], diff);
		}
#endif
    }
}

void setPwmWithLimit(int ch, SDEC ratio){
    if (ratio > torqueLimit.max[ch]) ratio = torqueLimit.max[ch];
    if (ratio < torqueLimit.min[ch]) ratio = torqueLimit.min[ch];
	setPwm(ch, ratio);
}

LDEC lastTorques[NMOTOR];
//	set motor power for PD control
void pdControl(){
	int i;
	for(i=0; i<NMOTOR; ++i){
		LDEC torque;
		LDEC diff = motorTarget.pos[i] - motorState.pos[i];
		int sign = pdParam.k[i] > 0 ? 1 : -1;
		if (diff > LDEC_ONE){
			torque = sign * LDEC_ONE;
		}else if (diff < -LDEC_ONE){
			torque = -sign * LDEC_ONE;
		}else{	// diff is less than 16 bits
			torque = (pdParam.k[i] * diff + 
				pdParam.b[i] * (motorTarget.vel[i] - motorState.vel[i])*32 );	//	b must be large for stability.
			torque >>= (SDEC_BITS-4);   //  k and b are SDEC. But x16 is done here.
			if (torque < -LDEC_ONE) torque = -LDEC_ONE;
			else if (torque > LDEC_ONE) torque = LDEC_ONE;
		}
#if 1	//	This reduce impulsive current
		const LDEC diffLimit = LDEC_ONE * 0.1;	//	smaller limit makes the control instable.
		LDEC torqueDiff = torque - lastTorques[i];
		if (torqueDiff > diffLimit){
			torque = lastTorques[i] + diffLimit;
		}
		if (torqueDiff < -diffLimit){
			torque = lastTorques[i] - diffLimit;
		}
		lastTorques[i] = torque;
#endif 
		setPwmWithLimit(i, L2SDEC(torque));
#if 0	//	to check pd control
		count ++;
		if (i==2 && count > 1000){
			count = 0;
			printf("G:%d  C:%d  T:%d\r\n", motorTarget.pos[i], motorState.pos[i], torque);
		}
#endif
	}
}

//----------------------------------------------------------------------------
//	Targets and interpolation
//
void targetsWrite(){
	if (targets.write < NTARGET-1){
			targets.write++;
	}else{
		targets.write = 0;
	}
}
//	Update or add interpolate target
void targetsAddOrUpdate(SDEC* pos, short period, unsigned char count){
	targetsForceControlAddOrUpdate(pos, NULL, period, count);
}
//	Update or add interpolate target with force control
void targetsForceControlAddOrUpdate(SDEC* pos, SDEC JK[NFORCE][NMOTOR] ,short period, unsigned char count){
	char delta;
	unsigned char avail, cor;
	LOGI("targetsAdd m0:%d pr:%d c:%d\r\n", (int)pos[0], (int)period, (int)count);
	if (period == 0) return;	//	for vacancy check
	
	//	check targets delta
	DISABLE_INTERRUPT
	avail = targetsReadAvail();
	cor = targets.countOfRead;
	ENABLE_INTERRUPT
	delta = count - cor;
	if (delta > avail){
		//	target count jumped. may be communication error.
		LOGE("CJ\r\n");
		targets.countOfRead = count - (avail-1);
	}
	
	/*	buf[0],[1] is currently used for interpolation. buf[2] will be used in the next step.
		So, we can update from buf[3] to buf[read + avail-1]. Also we can add to buf[read + avail]	*/
	if (delta == avail || (3 <= delta && delta < avail)){
		int i, j;
		int w = (targets.read + delta) % NTARGET;
		targets.buf[w].period = period;
		for(i=0; i<NMOTOR; ++i){
			targets.buf[w].pos[i] = pos[i];
		}
		if (JK){
			for(i=0; i<NMOTOR; ++i){
				for(j=0; j<NFORCE; ++j){
					targets.buf[w].Jacob[j][i] = JK[j][i];
				}
			}
		}
		LOGI("Write@%d a:%d p:%d c:%d", w, targetsReadAvail(), period, (int)count);
		if (w == targets.write){
			LOGI(" Add.\r\n");
			assert(delta == avail);
			if (targetsWriteAvail()){
				targetsWrite();
			}else{
				LOGE("Error: overflow of targets readCount shifted\r\n");
				targets.countOfRead ++;		//
			}
		}else{
			LOGI(" Update.\r\n");		
		}
	}
}
void targetsInit(){
	int i, j;
	targets.tick = 1;
	targets.read = 0;
	targets.write = 2;
	targets.countOfRead = 0x100 - 2;
	updateMotorState();
	targets.buf[0].period = 1;
	targets.buf[1].period = 1;
	for(i=0; i<NMOTOR; ++i){
		targets.buf[0].pos[i] = L2SDEC(motorState.pos[i]);
		targets.buf[1].pos[i] = L2SDEC(motorState.pos[i]);
		for(j=0; j<NFORCE; ++j){
			targets.buf[0].Jacob[j][i] = 0;
			targets.buf[1].Jacob[j][i] = 0;
			forceControlJK[j][i] = 0;
		}
	}
}
void targetsTickProceed(){
	targets.tick ++;
	if (targets.tick >= targets.buf[(targets.read+1)%NTARGET].period){
		if (targetsReadAvail() > 2){
			targets.tick = 0;
			targets.countOfRead ++;
			if (targets.read < NTARGET-1){
				targets.read ++;
			}else{
				targets.read = 0;
			}
			LOGI("Read=%d", targets.read);
		}else{
			targets.tick = targets.buf[(targets.read+1)%NTARGET].period;
		}
	}
}
void targetsProceed(){
	int i, readPlus;
	short period;
	targetsTickProceed();
	readPlus = (targets.read+1)%NTARGET;
	period = targets.buf[readPlus].period;
	for(i=0; i<NMOTOR; ++i){
#if 0
		motorTarget.pos[i] = ((period - targets.tick)* S2LDEC(targets.buf[targets.read].pos[i])
			+ targets.tick*S2LDEC(targets.buf[readPlus].pos[i])) / period;
#else
        SDEC diff = targets.buf[readPlus].pos[i] - targets.buf[(int)targets.read].pos[i];
        motorTarget.pos[i] = S2LDEC(targets.buf[(int)targets.read].pos[i]) + S2LDEC((int)diff * (int)targets.tick / period); 
#endif
		motorTarget.vel[i] = S2LDEC(targets.buf[readPlus].pos[i] - targets.buf[(int)targets.read].pos[i]) / period;
	}
}

LDEC deltaPosForceControl[NMOTOR];
void targetsForceControlProceed(){
	int i, j, readPlus;
	short period;
	targetsTickProceed();
	readPlus = (targets.read+1)%NTARGET;
	period = targets.buf[readPlus].period;
	for(i=0; i<NMOTOR; ++i){
        deltaPosForceControl[i] = (deltaPosForceControl[i] * ( 0x1000 - 1 )) >> 12; //  multiply (4096-1)/4096 
		for(j=0; j<NFORCE; ++j){
			forceControlJK[j][i] = ((period - targets.tick)* S2LDEC(targets.buf[(int)targets.read].Jacob[j][i])
			+ targets.tick*S2LDEC(targets.buf[readPlus].Jacob[j][i])) / period;
			deltaPosForceControl[i] += forceControlJK[j][i] * getForce(j);
		}
	}
	for(i=0; i<NMOTOR; ++i){
        SDEC diff = targets.buf[readPlus].pos[i] - targets.buf[(int)targets.read].pos[i];
        motorTarget.pos[i] = S2LDEC(targets.buf[(int)targets.read].pos[i]) + S2LDEC((int)diff * (int)targets.tick / period) + deltaPosForceControl[i];
		motorTarget.vel[i] = S2LDEC(targets.buf[readPlus].pos[i] - targets.buf[(int)targets.read].pos[i]) / period;
	}
}
void controlLoop(){
	controlCount ++;
    if (controlMode == CM_INTERPOLATE){
        targetsProceed();
    }else if (controlMode == CM_FORCE_CONTROL){
        targetsForceControlProceed();
	}
    updateMotorState();
	pdControl();
}
void controlInit(){
	int i;
	controlMode = CM_DIRECT;
	for(i=0; i<NMOTOR; ++i){
		pdParam.k[i] = SDEC_ONE;
		pdParam.b[i] = (SDEC)(SDEC_ONE * 1.5);
		torqueLimit.max[i] = SDEC_ONE;
		torqueLimit.min[i] = -SDEC_ONE;
	}
#ifdef PIC
	controlInitPic();
#endif
}
void controlSetMode(enum ControlMode m){
#ifdef PIC
	asm volatile("di"); // Disable all interrupts 
#endif
	if (controlMode != m){
		controlMode = m;
#ifdef PIC
		asm volatile("ei"); // Enable all interrupts 
#endif
		if (controlMode == CM_INTERPOLATE || controlMode == CM_FORCE_CONTROL){
			targetsInit();
		}
	}else{
#ifdef PIC
		asm volatile("ei"); // Enable all interrupts 
#endif
	}
}

void onControlTimer(){
#ifdef PIC
	LATCbits.LATC2 = 1;
#endif
	controlLoop();
#ifdef PIC
	LATCbits.LATC2 = 0;
#endif
}

#ifdef MODULETEST
void printMotorState(){
#if 1
    int i;
	for(i=0; i<NMOTOR; ++i){
        printf("%f\t", LDEC2DBL(motorState.pos[i]) );
    }
	for(i=0; i<NMOTOR; ++i){
        printf("%f\t", LDEC2DBL(motorState.vel[i]) );
    }
    printf("\n");
#endif
}
void printMotorTarget(){
    int i;
	for(i=0; i<NMOTOR; ++i){
        printf("%f\t", LDEC2DBL(motorTarget.pos[i]) );
    }
	for(i=0; i<NMOTOR; ++i){
        printf("%f\t", LDEC2DBL(motorTarget.vel[i]) );
    }
    printf("\n");
}
void printMotorControl(){
    int i;
	for(i=0; i<1; ++i){
        printf("%f\t", LDEC2DBL(motorTarget.pos[i]));
        printf("%f\t", LDEC2DBL(motorTarget.vel[i]));
        printf("%f\t", LDEC2DBL(motorState.pos[i]));
        printf("%f\t", LDEC2DBL(motorState.vel[i]));
        printf("%f\t", LDEC2DBL(motorTorques[i]) );
    }
    printf("\n");
}
#endif

