#include "env.h"
#include "decimal.h"
#include "mcc_generated_files/mcc.h"
#include "control.h"
#include "command.h"
#include "uart.h"
#include <stdio.h>

void outTest(int dir){
    static int pos;
	TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISB = 0x0000;
    TRISC = 0x0000;
	if (dir) pos ++;
	else pos --;
	
	if (pos < 0) pos = 16*3-1;
	if (pos >= 16*3) pos = 0;
	LATA = LATB = LATC = 0;
	if (pos < 16){
		LATA = 1 << pos;
		printf(" out A%d\r\n", pos);
	}else if (pos < 32){
		LATB = 1 << (pos-16);
		printf(" out B%d\r\n", (pos-16));
	}else{
		LATC = 1 << (pos-32);
		printf(" out C%d\r\n", (pos-32));
	}
}
void pwmTest(int dir){
	static SDEC pwmRatio;
	if (dir) pwmRatio += 1;
	else pwmRatio -=1;
	printf("pwm = %f\r\n", SDEC2DBL(pwmRatio));
	setPwm(0, pwmRatio);
	setPwm(1, pwmRatio);
	setPwm(2, pwmRatio);
	setPwm(3, pwmRatio);
}
void pwmTest2(){
	CCP1RA = 0;
	CCP1RB = 0x100;
	CCP2RA = 0;
	CCP2RB = 0x100;
	CCP3RA = 0;
	CCP3RB = 0x100;
	LATBbits.LATB6 = 1;	//	AIN1
	LATBbits.LATB7 = 0;	//	AIN2
	LATBbits.LATB5 = 1;	//	BIN1
	LATCbits.LATC3 = 0;	//	BIN2
	LATCbits.LATC9 = 1;	//	AIN1R
	LATCbits.LATC8 = 0;	//	AIN2R
	LATBbits.LATB10 = 1; // BIN1R
	LATBbits.LATB11 = 1; // BIN2R
}
struct MonitorFunc{
	char ch;
	char* desc;
	void (*func) ();
	bool callAgain;
};
void showAD(){
	int i;
	printf("ad");
	for(i=0; i<16; ++i) printf(" %x", *(&ADC1BUF0 + 4*i));
	printf("\r\n");
}
void showADInMotorOrder(){
	printf("Ad");
#if defined BOARD1_MOTORDRIVER
	printf(" %d %d ", ADC1BUF5, ADC1BUF2);
	printf(" %d %d ", ADC1BUF7, ADC1BUF6);
	printf(" %d %d ", ADC1BUF1, ADC1BUF0);
	printf(" %d %d\r\n", ADC1BUF4, ADC1BUF3);
#elif defined BOARD2_COMBINATION			
	printf(" %d %d ", ADC1BUF6, ADC1BUF7);
	printf(" %d %d ", ADC1BUF0, ADC1BUF1);
	printf(" %d %d ", ADC1BUF4, ADC1BUF9);
	printf(" %d %d\r\n", ADC1BUF10, ADC1BUF11);
#else
#error
#endif
}

void showControlStatus(){
	static uint32_t ct;
	if (ct != controlCount){
		ct = controlCount;
		printf("ctrl\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\r\n", 
				motorState.pos[0], motorTarget.pos[0], motorState.vel[0], motorTarget.vel[0], 
				targets.write, targets.read, targets.tick, targets.buf[(targets.read+1)%NTARGET].period, ct);
	}
}
void showCoreTimer(){
	printf("Core timer cur:%8x cmp:%8x remain:%5d\r\n", 
			_CP0_GET_COUNT(), _CP0_GET_COMPARE(), coretimerRemainTime);
}
void logLevelUp(){
	logLevel ++;
	printf("log level = %d", logLevel);
}
void logLevelDown(){
	logLevel --;
	printf("Log level = %d", logLevel);
}
void toggleControlTimer(){
	if (IEC0bits.CTIE){
		CORETIMER_DisableInterrupt();
		printf("stop timer interrupt.\r\n");
	}else{
		CORETIMER_Initialize();
		printf("Start timer interrupt.\r\n");
	}
}
void showUartState(){
	printf("uCSTA %8x", UCSTA);
	while(UCSTAbits.URXDA){
		printf(" %x", (int)UCRXREG);
	}
	printf("\r\n");
	printf("uMSTA %8x\r\n", UMSTA);
}
void showMotorRotation(){
	int i;
	printf("r");
	for(i=0; i<NMOTOR; ++i){
		printf(" %i=%2.3f (%d,%d)", i, LDEC2DBL(motorState.pos[i]), 
				mcos[i], msin[i]);
	}
	printf("\r\n");
}

static int motorCh;
static int pwm[NMOTOR];
void selectMotor(){
	motorCh++;
	if (motorCh >= NMOTOR) motorCh = 0;
	printf("Select motor %d. pww is %d\r\n", motorCh, pwm[motorCh]);
}
void pwmUp(){
	if (pwm[motorCh] < 10) pwm[motorCh] ++;
	printf("Set pwm %d to motor %d \r\n", pwm[motorCh], motorCh);
	setPwm(motorCh, pwm[motorCh] * (SDEC_ONE/10));
}
void pwmDown(){
	if (pwm[motorCh] > -10) pwm[motorCh] --;
	printf("Set pwm %d to motor %d \r\n", pwm[motorCh], motorCh);
	setPwm(motorCh, pwm[motorCh] * (SDEC_ONE/10));
}
struct MonitorFunc monitors[] = {
	{'a', "Show all A/D value", showAD, true},
	{'A', "Show A/D value in motor order", showADInMotorOrder, true},
	{'r', "Show motor rotation", showMotorRotation, true},
	{'c', "Show control status", showControlStatus, true},
	{'C', "Show core timer", showCoreTimer, true},
	{'u', "show uart status", showUartState, true},
	{'L', "Log level up", logLevelUp, false},
	{'l', "Log level down", logLevelDown, false},
	{'s', "toggle control timer", toggleControlTimer, false},
	{'m', "Select motor", selectMotor, false},
	{'P', "Pwm up", pwmUp, false},
	{'p', "Pwm down", pwmDown, false},
};
void showHelp(){
	int i;
	for(i=0; i<sizeof(monitors)/sizeof(monitors[0]); ++i){
		printf("%c: %s %c\r\n", monitors[i].ch, monitors[i].desc, monitors[i].callAgain ? 'R':' ');
	}
}

void monitor(){
	static int ch = 0;
	bool bHit = false;
	int i;
	if (UMSTAbits.URXDA){
		ch = UMRXREG;
	}
	for(i=0; i<sizeof(monitors)/sizeof(monitors[0]); ++i){
		if (ch == monitors[i].ch){
			monitors[i].func();
			bHit = true;
			if (monitors[i].callAgain == false){
				ch = 0;
			}
		}
	}
	if (!bHit && ch!=' ' && ch != 0){
		printf("'%c' is not used.\r\n", ch);
		showHelp();
		ch = 0;
	}
}
