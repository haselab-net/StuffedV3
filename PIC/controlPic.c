#include "env.h"

#include "fixed.h"
#include "control.h"
#include "mcc_generated_files/mcc.h"
#include <assert.h>

const SDEC mcosOffset[NAXIS] ={
    2048, 2048, 2048, 2048
};
const SDEC msinOffset[NAXIS] ={
    2048, 2048, 2048, 2048
};

inline short FilterForAngle(short prev, short cur){
    const short IIR = 16;
    return (prev*(IIR-1) + cur) / IIR;
}
inline short FilterForCurrent(short prev, short cur){
    const short IIR = 2;
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
#if defined BOARD1_MOTORDRIVER
    /*  ADC connection
     M1:  AN11, AN4 (cos, sin)
     M2:  AN13, AN12,    M3:  AN8, AN7,    M4:  AN1, AN0    */
    mcos[0] = FilterForAngle(mcos[0], ADC1BUF5 - mcosOffset[0]);
    msin[0] = FilterForAngle(msin[0], ADC1BUF2 - msinOffset[0]);
    mcos[1] = FilterForAngle(mcos[1], ADC1BUF7 - mcosOffset[1]);
    msin[1] = FilterForAngle(msin[1], ADC1BUF6 - msinOffset[1]);
	mcos[2] = FilterForAngle(mcos[2], ADC1BUF1 - mcosOffset[2]);
	msin[2] = FilterForAngle(msin[2], ADC1BUF0 - msinOffset[2]);
	mcos[3] = FilterForAngle(mcos[3], ADC1BUF4 - mcosOffset[3]);
	msin[3] = FilterForAngle(msin[3], ADC1BUF3 - msinOffset[3]);
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
    mcos[0] = FilterForAngle(mcos[0], ADC1BUF6 - mcosOffset[0]);
    msin[0] = FilterForAngle(msin[0], ADC1BUF7 - msinOffset[0]);
    mcos[1] = FilterForAngle(mcos[1], ADC1BUF0 - mcosOffset[1]);
    msin[1] = FilterForAngle(msin[1], ADC1BUF1 - msinOffset[1]);
	mcos[2] = FilterForAngle(mcos[2], ADC1BUF4 - mcosOffset[2]);
	msin[2] = FilterForAngle(msin[2], ADC1BUF9 - msinOffset[2]);
	mcos[3] = FilterForAngle(mcos[3], ADC1BUF10 - mcosOffset[3]);
	msin[3] = FilterForAngle(msin[3], ADC1BUF11 - msinOffset[3]);
#elif defined BOARD3_SEPARATE
/*  BUF 0 1 2 3  4 5 6 7  8   9 10 11
    AN  0 1 2 3  4 5 7 8 10  11 12 13 
    MT      2 3    5     10             */
	mcos[0] = FilterForAngle(mcos[0], ADC1BUF11 - mcosOffset[3]);
	msin[0] = FilterForAngle(msin[0], ADC1BUF10 - msinOffset[3]);
	mcos[1] = FilterForAngle(mcos[1], ADC1BUF4 - mcosOffset[2]);
	msin[1] = FilterForAngle(msin[1], ADC1BUF9 - msinOffset[2]);
    mcos[2] = FilterForAngle(mcos[2], ADC1BUF6 - mcosOffset[1]);
    msin[2] = FilterForAngle(msin[2], ADC1BUF7 - msinOffset[1]);
    mcos[3] = FilterForAngle(mcos[3], ADC1BUF0 - mcosOffset[0]);
    msin[3] = FilterForAngle(msin[3], ADC1BUF1 - msinOffset[0]);
    currentSense[0] = FilterForCurrent(currentSense[0], ADC1BUF5); //5
    currentSense[1] = FilterForCurrent(currentSense[1], ADC1BUF8); //10
    currentSense[2] = FilterForCurrent(currentSense[2], ADC1BUF2); //2
    currentSense[3] = FilterForCurrent(currentSense[3], ADC1BUF3); //3
#else
#error Board type not defined
#endif
}

#endif // else MODULE TEST


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

#if defined BOARD1_MOTORDRIVER
void setPwm(int ch, SDEC ratio){
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
#elif defined BOARD3_SEPARATE
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
		setSpiPwm(ratio);
    }
}
#else
#error
#endif

void __attribute__ ((vector(_SPI2_TX_VECTOR), interrupt(IPL6AUTO))) spiEmpty(void)
{
	SPI2BUF = spiPwm[0];
	SPI2BUF = spiPwm[1];
	SPI2BUF = spiPwm[0];
	SPI2BUF = spiPwm[1];
	IFS1CLR= 1 << _IFS1_SPI2TXIF_POSITION;
 }
void controlInitPic(){
    int i;
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
}
void onControlTimer(){
	LATCbits.LATC2 = 1;	//	LED ON
	controlLoop();
	LATCbits.LATC2 = 0;	//	LED OFF
}
