#include "decimal.h"
#include "control.h"
#include "mcc_generated_files/mcc.h"
#include <assert.h>

struct MotorState motorTarget, motorState;
SDEC forceControlJK[NFORCE][NMOTOR];
struct PdParam pdParam;
struct TorqueLimit torqueLimit;
struct Targets targets;
enum ControlMode controlMode;
//	 angle
SDEC mcos[NAXIS], msin[NAXIS];
const SDEC mcosOffset[NAXIS] ={
    2048, 2048, 2048, 2048
};
const SDEC msinOffset[NAXIS] ={
    2048, 2048, 2048, 2048
};
uint32_t controlCount;


inline short FilterForADC(short prev, short cur){
    const short IIR = 1;
    return (prev*(IIR-1) + cur) / IIR;
}
#ifdef MODULETEST
#include "math.h"
double motorAngle[NMOTOR]={0.0,0.0,0.0,0.0};
double motorVelocity[NMOTOR] = {0,0,0,0}; //{0.1, 0.1, 0.1, 0.1};
long motorTorques[NMOTOR];

//	device access
void readADC(){
    int i;
    for(i=0; i<NMOTOR;++i){
        mcos[i] = FilterForADC(mcos[i], cos(motorAngle[i])*2000);
        msin[i] = FilterForADC(msin[i], sin(motorAngle[i])*2000);
#if 1	// control test
		const double dt = 0.001;
        motorVelocity[i] += LDEC2DBL(motorTorques[i]) * dt * 10000;
        motorAngle[i] += motorVelocity[i] * dt;
#else
		motorAngle[i] += 0.4;
#endif
    }
}

#else

//----------------------------------------------------------------------------
//	device access
//
void readADC(){
#if defined BOARD1_MOTORDRIVER
    /*  ADC connection
     M1:  AN11, AN4 (cos, sin)
     M2:  AN13, AN12,    M3:  AN8, AN7,    M4:  AN1, AN0    */
    mcos[0] = FilterForADC(mcos[0], ADC1BUF5 - mcosOffset[0]);
    msin[0] = FilterForADC(msin[0], ADC1BUF2 - msinOffset[0]);
    mcos[1] = FilterForADC(mcos[1], ADC1BUF7 - mcosOffset[1]);
    msin[1] = FilterForADC(msin[1], ADC1BUF6 - msinOffset[1]);
	mcos[2] = FilterForADC(mcos[2], ADC1BUF1 - mcosOffset[2]);
	msin[2] = FilterForADC(msin[2], ADC1BUF0 - msinOffset[2]);
	mcos[3] = FilterForADC(mcos[3], ADC1BUF4 - mcosOffset[3]);
	msin[3] = FilterForADC(msin[3], ADC1BUF3 - msinOffset[3]);
#elif defined BOARD2_COMBINATION
    /*  ADC connection
     M1:  AN11, AN4 (cos, sin)
     M2:  AN13, AN12,    M3:  AN8, AN7,    M4:  AN1, AN0    */
    mcos[0] = FilterForADC(mcos[0], ADC1BUF0 - mcosOffset[0]);
    msin[0] = FilterForADC(msin[0], ADC1BUF1 - msinOffset[0]);
    mcos[1] = FilterForADC(mcos[1], ADC1BUF6 - mcosOffset[1]);
    msin[1] = FilterForADC(msin[1], ADC1BUF7 - msinOffset[1]);
	mcos[2] = FilterForADC(mcos[2], ADC1BUF3 - mcosOffset[2]);
	msin[2] = FilterForADC(msin[2], ADC1BUF9 - msinOffset[2]);
	mcos[3] = FilterForADC(mcos[3], ADC1BUF10 - mcosOffset[3]);
	msin[3] = FilterForADC(msin[3], ADC1BUF11 - msinOffset[3]);
#else
#error
#endif
}

#endif	//	MODULE TEST

//  PWM by SPI
unsigned long spiPwm[2];
inline void setSpiPwm(SDEC ratio){
	int pwm, pwm0;
	//	64bit = 0x40bit
	pwm = ratio * 0x40 >> SDEC_BITS;
	if (pwm < 2){
		spiPwm[0] = 0;
		if (pwm) spiPwm[1] = 1;
		else spiPwm[1] = 0;
	}else{
		pwm = 0x40 - pwm;
		if (pwm < 0) pwm = 0;
		pwm0 = pwm/2;
		pwm = pwm - pwm0;
		spiPwm[0] = 0xFFFFFFFF << pwm0;
		spiPwm[1] = 0xFFFFFFFF << pwm;
	}
}

void setPwm(int ch, SDEC ratio){
#ifdef MODULETEST
	motorTorques[ch] = S2LDEC(ratio);
#endif
    if (ratio > torqueLimit.max[ch]) ratio = torqueLimit.max[ch];
    if (ratio < torqueLimit.min[ch]) ratio = torqueLimit.min[ch];
	//	Connector at the left most.
    if (ch == 0){
#if defined BOARD1_MOTORDRIVER
		if (ratio < 0){
			ratio = -ratio;
			LATBbits.LATB5 = 0;	//	BIN1
			LATCbits.LATC3 = 1;	//	BIN2
		}else{
			LATBbits.LATB5 = 1;	//	BIN1
			LATCbits.LATC3 = 0;	//	BIN2
		}
		CCP3RA = 0;
		CCP3RB = (unsigned)CCP3PR * ratio >> SDEC_BITS;
#elif defined BOARD2_COMBINATION
		if (ratio < 0){
			ratio = -ratio;
			CCP1CON2bits.OCAEN = 1;
			CCP1CON2bits.OCBEN = 0;	//	this size is 0 = low
		}else{
			CCP1CON2bits.OCAEN = 0;
			CCP1CON2bits.OCBEN = 1;
		}
		CCP1RA = 0;
		CCP1RB = (unsigned)CCP1PR * ratio >> SDEC_BITS;
#endif
	//	Connector at second position from left
	}else if (ch == 1){
#if defined BOARD1_MOTORDRIVER
		if (ratio < 0){
			ratio = -ratio;
			LATBbits.LATB6 = 1;	//	AIN1
			LATBbits.LATB7 = 0;	//	AIN2
		}else{
			LATBbits.LATB6 = 0;	//	AIN1
			LATBbits.LATB7 = 1;	//	AIN2
		}
#elif defined BOARD2_COMBINATION
		if (ratio < 0){
			ratio = -ratio;
			RPOR1bits.RP6R = 6;		//	OCM2
			RPOR4bits.RP20R = 0;	//	NC(PIO))
		}else{
			RPOR1bits.RP6R = 0;		//	NC(PIO))
			RPOR4bits.RP20R = 6;	//	OCM2
		}
#endif
		CCP2RA = 0;
		CCP2RB = (unsigned)CCP2PR * ratio >> SDEC_BITS;
	//	Connector at third position from left
	}else if (ch == 2){
#if defined BOARD1_MOTORDRIVER
		if (ratio < 0){
			ratio = -ratio;
			LATBbits.LATB10 = 0; // BIN1R
			LATBbits.LATB11 = 1; // BIN2R
		}else{
			LATBbits.LATB10 = 1; // BIN1R
			LATBbits.LATB11 = 0; // BIN2R
		}
		setSpiPwm(ratio);
#elif defined BOARD2_COMBINATION
		if (ratio < 0){
			ratio = -ratio;
			RPOR1bits.RP6R = 7;		//	OCM3
			RPOR4bits.RP20R = 0;	//	NC(PIO))
		}else{
			RPOR1bits.RP6R = 0;		//	NC(PIO))
			RPOR4bits.RP20R = 7;	//	OCM3
		}
		CCP3RA = 0;
		CCP3RB = (unsigned)CCP3PR * ratio >> SDEC_BITS;
#endif
	//	Connector at right most
    }else{	
#if defined BOARD1_MOTORDRIVER
		if (ratio < 0){
			ratio = -ratio;
			LATCbits.LATC9 = 1;	//	AIN1R
			LATCbits.LATC8 = 0;	//	AIN2R
		}else{
			LATCbits.LATC9 = 0;	//	AIN1R
			LATCbits.LATC8 = 1;	//	AIN2R
		}
		CCP1RA = 0;
		CCP1RB = (unsigned)CCP1PR * ratio >> SDEC_BITS;
#elif defined BOARD2_COMBINATION
		if (ratio < 0){
			ratio = -ratio;
			RPOR4bits.RP19R = 3;		//	SDO2
			RPOR0bits.RP3R = 0;			//	NC(PIO))
		}else{
			RPOR4bits.RP19R = 0;		//	NC(PIO))
			RPOR0bits.RP3R = 3;			//	SDO2
		}		
		setSpiPwm(ratio);
#endif
    }
}
void __attribute__ ((vector(_SPI2_TX_VECTOR), interrupt(IPL6AUTO))) spiEmpty(void)
{
	SPI2BUF = spiPwm[0];
	SPI2BUF = spiPwm[1];
	SPI2BUF = spiPwm[0];
	SPI2BUF = spiPwm[1];
	IFS1CLR= 1 << _IFS1_SPI2TXIF_POSITION;
 }
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

//	set motor power for PD control
void pdControl(){
	static int count;
	int i;
	for(i=0; i<NMOTOR; ++i){
		LDEC torque;
		LDEC diff = motorTarget.pos[i] - motorState.pos[i];
		int sign = pdParam.k[i] > 0 ? 1 : -1;
		if (diff > LDEC_ONE*2){
			torque = sign * LDEC_ONE;
		}else if (diff < -LDEC_ONE*2){
			torque = -sign * LDEC_ONE;
		}else{
			torque = (pdParam.k[i] * diff + 
				pdParam.b[i] * (motorTarget.vel[i] - motorState.vel[i]) );
			torque >>= SDEC_BITS;   //  k and b are SDEC
			if (torque < -LDEC_ONE) torque = -LDEC_ONE;
			else if (torque > LDEC_ONE) torque = LDEC_ONE;
		}
		setPwm(i, L2SDEC(torque));
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
	asm volatile("di"); // Disable all interrupts 
	avail = targetsReadAvail();
	cor = targets.countOfRead;
	asm volatile("ei"); // Enable all interrupt	
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
					targets.buf[w].JK[j][i] = JK[j][i];
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
			targets.buf[0].JK[j][i] = 0;
			targets.buf[1].JK[j][i] = 0;
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
		motorTarget.pos[i] = ((period - targets.tick)* S2LDEC(targets.buf[targets.read].pos[i])
			+ targets.tick*S2LDEC(targets.buf[readPlus].pos[i])) / period;
		motorTarget.vel[i] = S2LDEC(targets.buf[readPlus].pos[i] - targets.buf[targets.read].pos[i]) / period;
	}
}
void targetsForceControlProceed(){
	int i, j, readPlus;
	short period;
	LDEC dPos[NMOTOR];
	targetsTickProceed();
	readPlus = (targets.read+1)%NTARGET;
	period = targets.buf[readPlus].period;
	for(i=0; i<NMOTOR; ++i){
		dPos[i] = 0;
		for(j=0; j<NFORCE; ++j){
			forceControlJK[j][i] = ((period - targets.tick)* S2LDEC(targets.buf[targets.read].JK[j][i])
			+ targets.tick*S2LDEC(targets.buf[readPlus].JK[j][i])) / period;
			dPos[i] += forceControlJK[j][i] * getForce(j);
		}
	}
	for(i=0; i<NMOTOR; ++i){
		motorTarget.pos[i] = ((period - targets.tick)* S2LDEC(targets.buf[targets.read].pos[i])
			+ targets.tick*S2LDEC(targets.buf[readPlus].pos[i])) / period + dPos[i];
		motorTarget.vel[i] = S2LDEC(targets.buf[readPlus].pos[i] - targets.buf[targets.read].pos[i]) / period;
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
//		pdParam.k[i] = SDEC_ONE / 20;
//		pdParam.b[i] = SDEC_ONE * 5;

		pdParam.k[i] = SDEC_ONE * 10;
		pdParam.b[i] = SDEC_ONE * 5;

		torqueLimit.max[i] = SDEC_ONE;
		torqueLimit.min[i] = -SDEC_ONE;
	}
#if 1
	//	disable interrupt
	IEC1bits.SPI2EIE = IEC1bits.SPI2RXIE = IEC1bits.SPI2TXIE = 0;
	i = SPI2BUF;	//	clear receive buf;
	IFS1bits.SPI2EIF = IFS1bits.SPI2RXIF = IFS1bits.SPI2TXIF = 0;
	IPC9bits.SPI2EIP = IPC9bits.SPI2EIS = IPC9bits.SPI2RXIP = IPC9bits.SPI2RXIS = 0;
	IPC9bits.SPI2TXIP = 5;
	IPC9bits.SPI2TXIS = 0;
	//	set spi2 control register
	SPI2CON = 0;
    SPI2CON = 0;
    SPI2CON2 = 0;
	SPI2STAT = 0;
    SPI2BRG = 0x00000077;
	SPI2CONbits.MODE32 = 1;
	SPI2CONbits.ENHBUF = 1;
	SPI2CONbits.MSTEN = 1;
	SPI2CONbits.STXISEL = 0x01;	//buffer is completly empty	
	SPI2CON2bits.IGNROV = 1;
	SPI2CON2bits.IGNTUR = 1;
	
	IEC1bits.SPI2TXIE = 1;	//	start interrupt
	SPI2CONbits.ON = 1;	//	SPI2 start	
	
	SPI2BUF = 0;
#endif
}
void controlSetMode(enum ControlMode m){
	
	asm volatile("di"); // Disable all interrupts 
	if (controlMode != m){
		controlMode = m;
		asm volatile("ei"); // Enable all interrupts 
		if (controlMode == CM_INTERPOLATE || controlMode == CM_FORCE_CONTROL){
			targetsInit();
		}
	}else{
		asm volatile("ei"); // Enable all interrupts 
	}
}

void onControlTimer(){
	LATCbits.LATC2 = 1;
	controlLoop();
	LATCbits.LATC2 = 0;
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

