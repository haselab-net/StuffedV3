#include "env.h"
#include "fixed.h"
#include "control.h"
#include <assert.h>


struct MotorState motorTarget, motorState;
SDEC currentTarget[NMOTOR]; //  Current target sent from host.
SDEC targetTorque[NMOTOR];  //  Previous target torque to fit the current to the target.
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
int underflowCount;

#ifdef WROOM
#define DISABLE_INTERRUPT	xSemaphoreTake(mutexForControl, portMAX_DELAY);
#define ENABLE_INTERRUPT	xSemaphoreGive(mutexForControl);
#endif
#ifdef PIC
#define DISABLE_INTERRUPT 	asm volatile("di"); // Disable all interrupts  
#define ENABLE_INTERRUPT	asm volatile("ei"); // Enable all interrupt	
#endif


#ifdef WROOM	//	Mutex for control
#include "freertos/FreeRTOS.h"
#include <freertos/task.h>
#include <freertos/semphr.h>
static xSemaphoreHandle mutexForControl;
#endif

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
			logPrintf("p %f,  s %f, (%d,%d) %d\r\n", LDEC2DBL(motorState.pos[i]), LDEC2DBL(sense), msin[i], mcos[i], diff);
		}
#endif
    }
}

inline void setPwmWithLimit(int ch, SDEC ratio){
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
		const LDEC diffLimit = (LDEC)(LDEC_ONE * 1);	//	smaller limit makes the control instable.
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
			logPrintf("G:%d  C:%d  T:%d\r\n", motorTarget.pos[i], motorState.pos[i], torque);
		}
#endif
	}
}
inline int truncate(int min, int val, int max){
    if (val < min) val = min;
    if (val > max) val = max;
    return val;
}
void currentControl(){
	int i;
    SDEC diff;
    int sign;
	for(i=0; i<NCURRENT && i<NMOTOR; ++i){
        if (currentTarget[i] > 0){
            diff = currentTarget[i] - currentSense[i];
            sign = 1;
        }else if (currentTarget[i] < 0){
            diff = -currentTarget[i] - currentSense[i];
            sign = -1;
        }else{
            sign = 0;
        }
        diff = (diff * pdParam.a[i]) >> SDEC_BITS;
        if (currentTarget[i] < 0) diff = -diff;
        targetTorque[i] += diff;
        if (sign > 0){
            if (targetTorque[i] < 0) targetTorque[i] = 0;
        }else if (sign < 0){
            if (targetTorque[i] > 0) targetTorque[i] = 0;
        }else{
            targetTorque[i] = 0;
        }
		setPwmWithLimit(i, targetTorque[i]);
    }
	for(; i < NMOTOR; ++i){
        targetTorque[i] = currentTarget[i];
		setPwmWithLimit(i, targetTorque[i]);        
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
	unsigned char avail, tcr, read;	//
	char delta;					//	tcr - count	
	if (period == 0) return;	//	for vacancy check
	
	//	check targets delta
	DISABLE_INTERRUPT
	read = targets.read;
	avail = targetsReadAvail();
	tcr = targets.targetCountRead;
	ENABLE_INTERRUPT
	delta = count - tcr;
	LOGI("targetsAdd m0:%d pr:%d c:%d | tcr=%d read=%d delta=%d\r\n", (int)pos[0], (int)period, (int)count, 
		(int)tcr, (int)read, (int)delta);
	if (delta > avail){
		//	target count jumped. may be communication error.
		LOGE("CJ\r\n");
		targets.targetCountRead = count - (avail-1);
	}
	
	/*	buf[0],[1] is currently used for interpolation. buf[2] will be used in the next step.
		So, we can update from buf[3] to buf[read + avail-1]. Also we can add to buf[read + avail]	*/
	if (delta == avail || (3 <= delta && delta < avail)){	//	add or update
		int i, j;
		int w = (read + delta) % NTARGET;
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
		LOGI("Write@%d ra:%d p:%d c:%d", w, avail, period, (int)count);
		if (w == targets.write){
			LOGI(" Add.\r\n");
			assert(delta == avail);
			if (targetsWriteAvail()){
				targetsWrite();
			}else{
				LOGE("Error: overflow of targets targetCountRead shifted\r\n");
				targets.targetCountRead = tcr + 1;
			}
		}else{
			LOGI(" Update.\r\n");		
		}
	}
}
void targetsInit(){
	/*
     * Initial state
     * buf[0] = buf[1] current position, period = 1.
     * interpolate between 0 and 1, ie. read=0, write=2
     * targetCountWrite start from 0. So targetCountRead start from -2.
     */
    int i, j;
	targets.tick = 1;
	targets.read = 0; 
	targets.write = 2;
	targets.targetCountRead = 0x100 - 2;
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
			targets.targetCountRead ++;
			if (targets.read < NTARGET-1){
				targets.read ++;
			}else{
				targets.read = 0;
			}
			LOGI("TickProceed: Read=%d tcr=%d\r\n", targets.read, targets.targetCountRead);
		}else{
			targets.tick = targets.buf[(targets.read+1)%NTARGET].period;
			LOGW("TickProceed: Underflow. Failed to increment read=%d tcr=%d\r\n", targets.read, targets.targetCountRead);
			underflowCount ++;
		}
	}
}
void targetsProceed(){
	int i, readPlus;
	short period;
	targetsTickProceed();
	readPlus = (targets.read+1)%NTARGET;
	period = targets.buf[readPlus].period;
	assert(period != 0);
	for(i=0; i<NMOTOR; ++i){
#if 0
		motorTarget.pos[i] = ((period - targets.tick)* S2LDEC(targets.buf[targets.read].pos[i])
			+ targets.tick*S2LDEC(targets.buf[readPlus].pos[i])) / period;
#else
        SDEC diff = targets.buf[readPlus].pos[i] - targets.buf[(int)targets.read].pos[i];
        motorTarget.pos[i] = S2LDEC(targets.buf[(int)targets.read].pos[i]) + S2LDEC((int)diff * (int)targets.tick / period); 
#endif
		motorTarget.vel[i] = S2LDEC(targets.buf[readPlus].pos[i] - targets.buf[(int)targets.read].pos[i]) / period;
#ifdef _WIN32
		filePrintf("%d,%d,", motorTarget.pos[i], motorTarget.vel[i]);
#endif
	}
#ifdef _WIN32
	filePrintf("\n");
#endif
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
	#ifdef WROOM
	xSemaphoreTake(mutexForControl, portMAX_DELAY);
	#endif
	controlCount ++;
    if (controlMode == CM_INTERPOLATE){
        targetsProceed();
    }else if (controlMode == CM_FORCE_CONTROL){
        targetsForceControlProceed();
	}
    updateMotorState();
	if (controlMode == CM_CURRENT){
        currentControl();
    }else{
        pdControl();
    }
	#ifdef WROOM
	xSemaphoreGive(mutexForControl);
	#endif
}
void controlInit(){
	int i;
	controlMode = CM_CURRENT;
	for(i=0; i<NMOTOR; ++i){
		pdParam.k[i] = SDEC_ONE;
		pdParam.b[i] = (SDEC)(SDEC_ONE * 1.5);
		pdParam.a[i] = (SDEC)(SDEC_ONE * 0.5);
		torqueLimit.max[i] = SDEC_ONE;
		torqueLimit.min[i] = -SDEC_ONE;
        currentTarget[i] = 0;
        targetTorque[i] = 0;
	}
#ifdef PIC
	controlInitPic();
#endif
#ifdef WROOM
	mutexForControl = xSemaphoreCreateMutex();
#endif
}
void controlSetMode(enum ControlMode m){
	if (controlMode != m){
#ifdef WROOM
    	DISABLE_INTERRUPT
#endif
		if (m == CM_INTERPOLATE || m == CM_FORCE_CONTROL){
			targetsInit();
		}
#ifdef PIC
    	DISABLE_INTERRUPT
#endif
		controlMode = m;
    	ENABLE_INTERRUPT
	}
}

#ifdef MODULETEST
void printMotorState(){
#if 1
    int i;
	for(i=0; i<NMOTOR; ++i){
        logPrintf("%f\t", LDEC2DBL(motorState.pos[i]) );
    }
	for(i=0; i<NMOTOR; ++i){
        logPrintf("%f\t", LDEC2DBL(motorState.vel[i]) );
    }
    logPrintf("\n");
#endif
}
void printMotorTarget(){
    int i;
	for(i=0; i<NMOTOR; ++i){
        logPrintf("%f\t", LDEC2DBL(motorTarget.pos[i]) );
    }
	for(i=0; i<NMOTOR; ++i){
        logPrintf("%f\t", LDEC2DBL(motorTarget.vel[i]) );
    }
    logPrintf("\n");
}
void printMotorControl(){
    int i;
	for(i=0; i<1; ++i){
        logPrintf("%f\t", LDEC2DBL(motorTarget.pos[i]));
        logPrintf("%f\t", LDEC2DBL(motorTarget.vel[i]));
        logPrintf("%f\t", LDEC2DBL(motorState.pos[i]));
        logPrintf("%f\t", LDEC2DBL(motorState.vel[i]));
        logPrintf("%f\t", LDEC2DBL(motorTorques[i]) );
    }
    logPrintf("\n");
}
#endif

