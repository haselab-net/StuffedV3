#include "env.h"

#include "fixed.h"
#include "control.h"
#ifdef PIC32MM
#include "mcc_generated_files/mcc.h"
#else
#include "definitions.h"
#endif
#include "nvm.h"
#include <assert.h>

#include "spiPwmDefs.h"
#include "controlPic.h"


SDEC mcosOffset[NAXIS] ={
    2048, 2048, 2048, 2048
};
SDEC msinOffset[NAXIS] ={
    2048, 2048, 2048, 2048
};

SDEC mcosRaw[NAXIS];
SDEC msinRaw[NAXIS];

//  for auto calibration
SDEC mcosMin[NAXIS] = {0,0,0,0};
SDEC mcosMax[NAXIS] = {0,0,0,0};
SDEC msinMin[NAXIS] = {0,0,0,0};
SDEC msinMax[NAXIS] = {0,0,0,0};
#define OFFSET  2048
#define AMPLITUDE   (OFFSET*0.9)
SDEC mcosMinAve[NAXIS] = {OFFSET-AMPLITUDE, OFFSET-AMPLITUDE, OFFSET-AMPLITUDE, OFFSET-AMPLITUDE};
SDEC mcosMaxAve[NAXIS] = {OFFSET+AMPLITUDE, OFFSET+AMPLITUDE, OFFSET+AMPLITUDE, OFFSET+AMPLITUDE};
SDEC msinMinAve[NAXIS] = {OFFSET-AMPLITUDE, OFFSET-AMPLITUDE, OFFSET-AMPLITUDE, OFFSET-AMPLITUDE};
SDEC msinMaxAve[NAXIS] = {OFFSET+AMPLITUDE, OFFSET+AMPLITUDE, OFFSET+AMPLITUDE, OFFSET+AMPLITUDE};

#define SCALE   (4096*4096) / (AMPLITUDE*2)
SDEC mcosScale[NAXIS] = {SCALE, SCALE, SCALE, SCALE};
SDEC msinScale[NAXIS] = {SCALE, SCALE, SCALE, SCALE};

/*  Rotation State
 *  State will change with hysteresis. 1->2: cos=+ > -E, 1->4: sin=+>-E
 *  1<->2: aquire sinMax and rest to 0
 *  3<->4: aquire sinMin and rest to 0
 *  2<->3: aquire cosMin and rest to 0
 *  4<->1: aquire cosMax and rest to 0
 */
enum RotationState {
    UNKNOWN,
    QUADRANT_1, //  cos+, sin+
    QUADRANT_2, //  cos-, sin+
    QUADRANT_3, //  cos-, sin-
    QUADRANT_4, //  cos+, sin-
} rotationState[NAXIS] = {UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN};


inline short FilterForAngle(short prev, short cur){
    const short IIR = 16;
    return (prev*(IIR-1) + cur) / IIR;
}
inline short FilterForCurrent(short prev, short cur){
    const short IIR = 2;
    return (prev*(IIR-1) + cur) / IIR;
}
inline short FilterForMinMax(short prev, short cur){
    const short IIR = 16;
    return (prev*(IIR-1) + cur) / IIR;
}

inline void updateAverageAndScale(int idx){
    SDEC mcosDiff = mcosMaxAve[idx] - mcosMinAve[idx];
    SDEC msinDiff = msinMaxAve[idx] - msinMinAve[idx];
    mcosScale[idx] = 4096*4096 / mcosDiff;
    msinScale[idx] = 4096*4096 / msinDiff;
    mcosOffset[idx] = mcosMinAve[idx] + mcosDiff/2;
    msinOffset[idx] = msinMinAve[idx] + msinDiff/2;
}

inline void updateRotationState(int idx){
    const SDEC E = SDEC_ONE / 16;
    switch(rotationState[idx]){
        case QUADRANT_1:
            if (mcos[idx] < -E) {
                rotationState[idx] = QUADRANT_2;
                msinMaxAve[idx] = FilterForMinMax(msinMaxAve[idx], msinMax[idx]);
                msinMax[idx] = 0;
            }else if (msin[idx] < -E){
                rotationState[idx] = QUADRANT_4;
                mcosMaxAve[idx] = FilterForMinMax(mcosMaxAve[idx], mcosMax[idx]);
                mcosMax[idx] = 0;
                updateAverageAndScale(idx);
            }
            break;
        case QUADRANT_2:
            if (mcos[idx] > E){
                rotationState[idx] = QUADRANT_1;
                msinMaxAve[idx] = FilterForMinMax(msinMaxAve[idx], msinMax[idx]);
                msinMax[idx] = 0;
            }else if (msin[idx] < -E){
                rotationState[idx] = QUADRANT_3;
                mcosMinAve[idx] = FilterForMinMax(mcosMinAve[idx], mcosMin[idx]);
                mcosMin[idx] = 0;
            }
            break;
        case QUADRANT_3:
            if (mcos[idx] > E){
                rotationState[idx] = QUADRANT_4;
                msinMinAve[idx] = FilterForMinMax(msinMinAve[idx], msinMin[idx]);
                msinMin[idx] = 0;
            }else if (msin[idx] > E){
                rotationState[idx] = QUADRANT_2;
                mcosMinAve[idx] = FilterForMinMax(mcosMinAve[idx], mcosMin[idx]);
                mcosMin[idx] = 0;
            }
            break;            
        case QUADRANT_4:
            if (mcos[idx] < -E){
                rotationState[idx] = QUADRANT_3;
                msinMinAve[idx] = FilterForMinMax(msinMinAve[idx], msinMin[idx]);
                msinMin[idx] = 0;
            }else if (msin[idx] > E){
                rotationState[idx] = QUADRANT_1;
                mcosMaxAve[idx] = FilterForMinMax(mcosMaxAve[idx], mcosMax[idx]);
                mcosMax[idx] = 0;
                updateAverageAndScale(idx);
            }
            break;
        default:
            if (msin[idx] > 0){
                if (mcos[idx] > 0) rotationState[idx] = QUADRANT_1;
                else rotationState[idx] = QUADRANT_2;
            }else{
                if (mcos[idx] > 0) rotationState[idx] = QUADRANT_4;
                else rotationState[idx] = QUADRANT_3;
            }
            break;
    }
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
        mcos[i] = FilterForAngle(mcos[i], cos(motorAngle[i])*2000);
        msin[i] = FilterForAngle(msin[i], sin(motorAngle[i])*2000);
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
#if defined PIC32MM
#if defined BOARD1_MOTORDRIVER
    /*  ADC connection
     M1:  AN11, AN4 (cos, sin)
     M2:  AN13, AN12,    M3:  AN8, AN7,    M4:  AN1, AN0    */
    mcosRaw[0] = FilterForAngle(mcosRaw[0], ADC1BUF5);
    msinRaw[0] = FilterForAngle(msinRaw[0], ADC1BUF2);
    mcosRaw[1] = FilterForAngle(mcosRaw[1], ADC1BUF7);
    msinRaw[1] = FilterForAngle(msinRaw[1], ADC1BUF6);
	mcosRaw[2] = FilterForAngle(mcosRaw[2], ADC1BUF1);
	msinRaw[2] = FilterForAngle(msinRaw[2], ADC1BUF0);
	mcosRaw[3] = FilterForAngle(mcosRaw[3], ADC1BUF4);
	msinRaw[3] = FilterForAngle(msinRaw[3], ADC1BUF3);
#elif defined BOARD2_COMBINATION
    /*  ADC connection
     M1:  AN11, AN4 (cos, sin)
     M2:  AN13, AN12,    M3:  AN8, AN7,    M4:  AN1, AN0    
	 
AN7 AN8		6 7 
AN0 AN1		0 1
AN4 AN11	4 9
AN12 AN13	10 11

BUF 0 1 2 3  4 5 6 7  8   9 10 11
AN  0 1 2 3  4 5 7 8 10  11 12 13 
AN      2 3    5     10         
*/
    mcosRaw[0] = FilterForAngle(mcosRaw[0], ADC1BUF6 );
    msinRaw[0] = FilterForAngle(msinRaw[0], ADC1BUF7 );
    mcosRaw[1] = FilterForAngle(mcosRaw[1], ADC1BUF0 );
    msinRaw[1] = FilterForAngle(msinRaw[1], ADC1BUF1 );
	mcosRaw[2] = FilterForAngle(mcosRaw[2], ADC1BUF4 );
	msinRaw[2] = FilterForAngle(msinRaw[2], ADC1BUF9 );
	mcosRaw[3] = FilterForAngle(mcosRaw[3], ADC1BUF10);
	msinRaw[3] = FilterForAngle(msinRaw[3], ADC1BUF11);
#elif defined BOARD3_SEPARATE || defined BOARD4
/*  BUF 0 1 2 3  4 5 6 7  8   9 10 11
    AN  0 1 2 3  4 5 7 8 10  11 12 13 
    MT      2 3    5     10             */
	mcosRaw[0] = FilterForAngle(mcosRaw[0], ADC1BUF11);
	msinRaw[0] = FilterForAngle(msinRaw[0], ADC1BUF10);
	mcosRaw[1] = FilterForAngle(mcosRaw[1], ADC1BUF4 );
	msinRaw[1] = FilterForAngle(msinRaw[1], ADC1BUF9 );
    mcosRaw[2] = FilterForAngle(mcosRaw[2], ADC1BUF6 );
    msinRaw[2] = FilterForAngle(msinRaw[2], ADC1BUF7 );
    mcosRaw[3] = FilterForAngle(mcosRaw[3], ADC1BUF0 );
    msinRaw[3] = FilterForAngle(msinRaw[3], ADC1BUF1 );
    currentSense[0] = FilterForCurrent(currentSense[0], ADC1BUF5); //5
    currentSense[1] = FilterForCurrent(currentSense[1], ADC1BUF8); //10
    currentSense[2] = FilterForCurrent(currentSense[2], ADC1BUF2); //2
    currentSense[3] = FilterForCurrent(currentSense[3], ADC1BUF3); //3
#else
#error Board type not defined
#endif
#elif defined PIC32MK_MCJ
//Force	AN16-10, AN27-25

//Angle1-4:	AN41-24, AN47-46, AN48-49, AN6-5, 
	mcosRaw[0] = FilterForAngle(mcosRaw[0], ADCDATA41);
	msinRaw[0] = FilterForAngle(msinRaw[0], ADCDATA24);
	mcosRaw[1] = FilterForAngle(mcosRaw[1], ADCDATA47);
	msinRaw[1] = FilterForAngle(msinRaw[1], ADCDATA46);
    mcosRaw[2] = FilterForAngle(mcosRaw[2], ADCDATA48);
    msinRaw[2] = FilterForAngle(msinRaw[2], ADCDATA49);
    mcosRaw[3] = FilterForAngle(mcosRaw[3], ADCDATA6);
    msinRaw[3] = FilterForAngle(msinRaw[3], ADCDATA5);

//Angle5-8: AN7-8, AN13-11, AN14-12, AN15-26
	mcosRaw[4] = FilterForAngle(mcosRaw[4], ADCDATA7);
	msinRaw[4] = FilterForAngle(msinRaw[4], ADCDATA8);
	mcosRaw[5] = FilterForAngle(mcosRaw[5], ADCDATA13);
	msinRaw[5] = FilterForAngle(msinRaw[5], ADCDATA11);
    mcosRaw[6] = FilterForAngle(mcosRaw[6], ADCDATA14);
    msinRaw[6] = FilterForAngle(msinRaw[6], ADCDATA12);
    mcosRaw[7] = FilterForAngle(mcosRaw[7], ADCDATA15);
    msinRaw[7] = FilterForAngle(msinRaw[7], ADCDATA26);

//Force	AN16-10, AN27-25
    mcosRaw[8] = FilterForCurrent(currentSense[0], ADCDATA16);
    msinRaw[8] = FilterForCurrent(currentSense[1], ADCDATA10);
    mcosRaw[9] = FilterForCurrent(currentSense[2], ADCDATA27); //2
    msinRaw[9] = FilterForCurrent(currentSense[3], ADCDATA25); //3
#endif

	//	update mcos msin
    int i;
    for(i=0; i<NAXIS; ++i){
    	mcos[i] = (int)(mcosRaw[i] - mcosOffset[i]) * mcosScale[i] / SDEC_ONE;
    	msin[i] = (int)(msinRaw[i] - msinOffset[i]) * msinScale[i] / SDEC_ONE;
    }
    //  update min max rotation state
    for(i=0; i<NAXIS; ++i){
        if (mcosRaw[i] > mcosMax[i]) mcosMax[i] = mcosRaw[i];
        else if (mcosRaw[i] < mcosMin[i]) mcosMin[i] = mcosRaw[i];
        if (msinRaw[i] > msinMax[i]) msinMax[i] = msinRaw[i];
        else if (msinRaw[i] < msinMin[i]) msinMin[i] = msinRaw[i];
        updateRotationState(i);
    }
}

#endif // else MODULE TEST


//  PWM by SPI
extern unsigned long spiPwmWord1;
extern unsigned long spiPwmWord2;
#ifdef SPIPWM128
extern unsigned long spiPwmWord3;
extern unsigned long spiPwmWord4;
#endif

inline void setSpiPwm64(SDEC ratio){
	int pwm, pwm0;
	//	64bit = 0x40bit
	pwm = ratio * 0x40 >> SDEC_BITS;
	if (pwm < 2){
		spiPwmWord1 = 0;
		if (pwm) spiPwmWord2 = 1;
		else spiPwmWord2 = 0;
	}else{
		pwm = 0x40 - pwm;
		if (pwm < 0) pwm = 0;
		pwm0 = pwm/2;
		pwm = pwm - pwm0;
		spiPwmWord1 = 0xFFFFFFFF << pwm0;
		spiPwmWord2 = 0xFFFFFFFF << pwm;
	}
}
inline void setSpiPwm128(SDEC ratio){
	short zeroLen;
	//	128 = 7bit
	zeroLen = 128 - (ratio >> (SDEC_BITS - 7));
//    if (pwm < 0) pwm = 0;
    short zeroLen1 = zeroLen >> 2;
    short zeroLen24 = zeroLen1 + ((zeroLen >> 1) & 0x1);
    short zeroLen3 = zeroLen1 + (zeroLen & 0x1);
    spiPwmWord1 = zeroLen1==32 ? 0 : (0xFFFFFFFF << zeroLen1);
    spiPwmWord2 = spiPwmWord4 = zeroLen24==32 ? 0 : (0xFFFFFFFF << zeroLen24);
    spiPwmWord3 = zeroLen3==32 ? 0 : (0xFFFFFFFF << zeroLen3);
}

#if defined BOARD1_MOTORDRIVER
void 

(int ch, SDEC ratio){
	//	Connector at the left most.
    if (ch == 0){
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
	}else if (ch == 1){	//	Connector at second position from left
		if (ratio < 0){
			ratio = -ratio;
			LATBbits.LATB6 = 1;	//	AIN1
			LATBbits.LATB7 = 0;	//	AIN2
		}else{
			LATBbits.LATB6 = 0;	//	AIN1
			LATBbits.LATB7 = 1;	//	AIN2
		}
		CCP2RA = 0;
		CCP2RB = (unsigned)CCP2PR * ratio >> SDEC_BITS;
	}else if (ch == 2){
		if (ratio < 0){
			ratio = -ratio;
			LATBbits.LATB10 = 0; // BIN1R
			LATBbits.LATB11 = 1; // BIN2R
		}else{
			LATBbits.LATB10 = 1; // BIN1R
			LATBbits.LATB11 = 0; // BIN2R
		}
		setSpiPwm(ratio);
    }else{	
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
    }
}
#elif defined BOARD2_COMBINATION
void setPwm(int ch, SDEC ratio){
    if (ch == 0){
		if (ratio < 0){
			ratio = -ratio;
			RPOR1bits.RP6R = 0;		//	NC(PIO))
			RPOR4bits.RP20R = 6;	//	OCM2
		}else{
			RPOR1bits.RP6R = 6;		//	OCM2
			RPOR4bits.RP20R = 0;	//	NC(PIO))
		}
		CCP2RA = 0;
		CCP2RB = (unsigned)CCP2PR * ratio >> SDEC_BITS;
	}else if (ch == 1){	//	Connector at second position from left
		if (ratio < 0){
			ratio = -ratio;
			CCP1CON2bits.OCAEN = 0;
			CCP1CON2bits.OCBEN = 1;
		}else{
			CCP1CON2bits.OCAEN = 1;
			CCP1CON2bits.OCBEN = 0;
		}
		CCP1RA = 0;
		CCP1RB = (unsigned)CCP1PR * ratio >> SDEC_BITS;
	}else if (ch == 2){
		if (ratio < 0){
			ratio = -ratio;
			RPOR1bits.RP5R = 7;		//	OCM3
			RPOR2bits.RP11R = 0;	//	NC(PIO))
		}else{
			RPOR1bits.RP5R = 0;		//	NC(PIO))
			RPOR2bits.RP11R = 7;	//	OCM3
		}
		CCP3RA = 0;
		CCP3RB = (unsigned)CCP3PR * ratio >> SDEC_BITS;
    }else{	
		if (ratio < 0){
			ratio = -ratio;
			RPOR4bits.RP19R = 0;		//	NC(PIO))
			RPOR0bits.RP4R = 3;			//	SDO2
		}else{
			RPOR4bits.RP19R = 3;		//	SDO2
			RPOR0bits.RP4R = 0;			//	NC(PIO))
		}		
		setSpiPwm(ratio);
    }
}
#elif defined BOARD3_SEPARATE || defined BOARD4
void setPwm(int ch, SDEC ratio){
    if (ch == 0){   //  M0=LCP4  U2B1/2=OCM1B/A
		if (ratio < 0){
			ratio = -ratio;
			CCP1CON2bits.OCAEN = 0;
			CCP1CON2bits.OCBEN = 1; //  OCM1B
		}else{
			CCP1CON2bits.OCAEN = 1; //  OCM1A
			CCP1CON2bits.OCBEN = 0;
		}
		CCP1RA = 0;
		CCP1RB = (unsigned)CCP1PR * ratio >> SDEC_BITS;
	}else if (ch == 1){	//  M1=LCP3  U2A2/1=OCM2A/B
		if (ratio < 0){
			ratio = -ratio;
			RPOR1bits.RP6R = 6;		//	OCM2A
			RPOR4bits.RP20R = 0;	//	NC(PIO))
		}else{
			RPOR1bits.RP6R = 0;		//	NC(PIO))
			RPOR4bits.RP20R = 6;	//	OCM2B
		}
		CCP2RA = 0;
		CCP2RB = (unsigned)CCP2PR * ratio >> SDEC_BITS;
	}else if (ch == 2){
		if (ratio < 0){ //  M2=LCP2  U1B1/2=OCM3A/B
			ratio = -ratio;
			RPOR1bits.RP5R = 7;		//	=RB4: OCM3A
			RPOR2bits.RP11R = 0;	//	NC(PIO))
		}else{
			RPOR1bits.RP5R = 0;		//	NC(PIO))
			RPOR2bits.RP11R = 7;	//	=RB7: OCM3B
		}
		CCP3RA = 0;
		CCP3RB = (unsigned)CCP3PR * ratio >> SDEC_BITS;
    }else{	
		if (ratio < 0){ //  M3=LCP1 
			ratio = -ratio;
			RPOR4bits.RP19R = 3;	//=RC9:	SDO2
			RPOR0bits.RP4R = 0;		//	NC(PIO))
		}else{
			RPOR4bits.RP19R = 0;	//	NC(PIO))
			RPOR0bits.RP4R = 3;		//=RA3:	SDO2
		}
#ifdef SPIPWM128
		setSpiPwm128(ratio);
#elif defined SPIPWM64
		setSpiPwm64(ratio);
#endif
    }
}
#elif defined BOARD5
void setPHLevel(int ch, int val){
    //printf("setPHLevel(%d, %d)", ch, val);
    switch(ch){
        case 0:
            val ? GPIO_RB4_Set() : GPIO_RB4_Clear();     //  APH0
            break;    
        case 1:
            val ? GPIO_RA15_Set() : GPIO_RA15_Clear();   //  BPH0
            break;    
        case 2:
            val ? GPIO_RD8_Set() : GPIO_RD8_Clear();
            break;    
        case 3:
            val ? GPIO_RC12_Set() : GPIO_RC12_Clear();
            break;
        case 4:
            val ? GPIO_RC10_Set() : GPIO_RC10_Clear();
            break;    
        case 5:
            val ? GPIO_RB7_Set() : GPIO_RB7_Clear();
            break;    
        case 6:
            val ? GPIO_RF0_Set() : GPIO_RF0_Clear();
            break;    
        case 7:
            val ? GPIO_RD6_Set() : GPIO_RD6_Clear();
            break;    
    }
}
void setPwm(int ch, SDEC ratio){
    #define PWM_PERIOD  50
    int reverse = 0;
    if (ratio < 0){
        ratio = -ratio;
        reverse = 1;
    }
    int pwm = (((int)ratio) * PWM_PERIOD) >> SDEC_BITS;
    MCPWM_ChannelPrimaryDutySet(ch, pwm);
    setPHLevel(ch, reverse);
}
#else
#error
#endif

#if 0

unsigned long spiPwmWord1;
unsigned long spiPwmWord2;

void __attribute__ ((vector(_SPI2_TX_VECTOR), interrupt(IPL6AUTO))) spiEmpty(void)
{
	SPI2BUF = spiPwmWord1;
	SPI2BUF = spiPwmWord2;
	SPI2BUF = spiPwmWord1;
	SPI2BUF = spiPwmWord2;
	IFS1CLR= 1 << _IFS1_SPI2TXIF_POSITION;
 }
#endif


extern unsigned int addrSPI2BUF;

void controlInitPic(){
#ifdef PIC32MM
    addrSPI2BUF = (unsigned int)&SPI2BUF;
	//	disable interrupt
	IEC1bits.SPI2EIE = IEC1bits.SPI2RXIE = IEC1bits.SPI2TXIE = 0;
	int i = SPI2BUF;	//	clear receive buf;
	IFS1bits.SPI2EIF = IFS1bits.SPI2RXIF = IFS1bits.SPI2TXIF = 0;
	IPC9bits.SPI2EIP = IPC9bits.SPI2EIS = IPC9bits.SPI2RXIP = IPC9bits.SPI2RXIS = 0;
	IPC9bits.SPI2TXIP = 5;
	IPC9bits.SPI2TXIS = 0;
	//	set spi2 control register
	SPI2CON = 0;
    SPI2CON2 = 0;
	SPI2STAT = 0;
//    SPI2BRG = 0x00000010; //  squeal sound caused by PWM is a bit noisy
//    SPI2BRG = 0x0000000C;   //  Small squeal sound can be heard.
    SPI2BRG = 0x0000000A;   //  Very small squeal sound can be heard. Noise occurs but small.
//    SPI2BRG = 0x00000008; //  noise caused by unstable pulse width occur around 64.
//    SPI2BRG = 0x00000004; //  noise caused by unstable pulse width occur around 64.
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
void onControlTimer(){
#ifdef PIC32MM
	LATCbits.LATC2 = 1;	//	LED ON
	controlLoop();
	LATCbits.LATC2 = 0;	//	LED OFF
#elif PIC32MK_MCJ
	controlLoop();
#else
#error
#endif
}


///	motor paramters
void saveMotorParam(){
	NvData nvData;
    int i;
	NVMRead(&nvData);
    for(i=0; i<NMOTOR; ++i){
        nvData.param.k[i] = pdParam.k[i];
        nvData.param.b[i] = pdParam.b[i];
        nvData.param.a[i] = pdParam.a[i];
        if (motorHeatRelease[i] < 1) motorHeatRelease[i] = 1;
        nvData.heat.release[i] = 	motorHeatRelease[i];
        nvData.heat.limit[i] = motorHeatLimit[i] / motorHeatRelease[i];
    }
    NVMWrite(&nvData);
}
void loadMotorParam(){
    int i;
    for(i=0; i<NMOTOR; ++i){
        pdParam.k[i] = PNVDATA->param.k[i];
        pdParam.b[i] = PNVDATA->param.b[i];
        pdParam.a[i] = PNVDATA->param.a[i];
        motorHeatRelease[i] = PNVDATA->heat.release[i];	
        motorHeatLimit[i] = PNVDATA->heat.limit[i] * PNVDATA->heat.release[i];
    }
}
