#include "env.h"
#include "fixed.h"
#include "control.h"
#include "command.h"
#include "uart.h"
#include "nvm.h"
#include <stdio.h>
#ifdef PIC32MK_MCJ
#include "embeddedFramework.h"
#endif

extern bool monOut();

void outTest(int dir){
    static int pos;
	TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
#ifdef PIC32MM
    TRISAbits.TRISA2 = 0;
#endif
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
#ifdef PIC32MM
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
#else
#endif
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
#ifdef PIC32MM
	for(i=0; i<16; ++i) printf(" %x", *(&ADC1BUF0 + 4*i));
#elif defined PIC32MK_MCJ
	for(i=0; i<64; ++i) printf(" %x", *(&ADCDATA0 + 4*i));    
#else
#error
#endif
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
#elif defined BOARD3_SEPARATE || defined BOARD4
	//  motor angle
    printf(" Angle: %d %d ", ADC1BUF0, ADC1BUF1);
	printf(" %d %d ", ADC1BUF6, ADC1BUF7);
	printf(" %d %d ", ADC1BUF4, ADC1BUF9);
	printf(" %d %d ", ADC1BUF11, ADC1BUF10);
    //  current
	printf(" Current: %d %d %d %d\r\n", ADC1BUF5, ADC1BUF8, ADC1BUF2, ADC1BUF3);    
#elif defined BOARD5
	//  motor angle
    printf(" Angle: %d %d ", ADCDATA9, ADCDATA10);
	printf(" %d %d ", ADCDATA1, ADCDATA0);
	printf(" %d %d ", ADCDATA3, ADCDATA2);
	printf(" %d %d ", ADCDATA4, ADCDATA5);
	printf(" %d %d ", ADCDATA6, ADCDATA7);
	printf(" %d %d ", ADCDATA11, ADCDATA8);
	printf(" %d %d ", ADCDATA12, ADCDATA13);
	printf(" %d %d ", ADCDATA14, ADCDATA15);
/*
AN9,10: M0,1
AN1,0: M2,3
AN3,2: M4,5
AN4,5: M6,7
AN6,7: M8,9
AN11,8: M10,11
AN12,13: M12,13
AN14,15: M14,15
 */

    //  force
	printf(" Force: %d %d %d %d\r\n", ADCDATA24, ADCDATA26, ADCDATA46, ADCDATA41);
#else
#error
#endif
}

void showControlStatus(){
	static uint32_t ct;
	if (ct != controlCount){
		ct = controlCount;
		printf("ctrl\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\r\n", 
				(int)motorState.pos[0], (int)motorTarget.pos[0], (int)motorState.vel[0], (int)motorTarget.vel[0], 
				(int)targets.write, (int)targets.read, (int)targets.tick, (int)targets.buf[(targets.read+1)%NTARGET].period, ct);
	}
}
void showControlTimer(){
#if defined PIC32MM
	printf("Core timer cur:%8x cmp:%8x remain:%5d\r\n", 
			_CP0_GET_COUNT(), _CP0_GET_COMPARE(), coretimerRemainTime);
#elif defined PIC32MK_MCJ
	printf("Timer2 cur:%8x cmp:%8x remain:%5d\r\n", 
			TMR2_CounterGet() , TMR2_PeriodGet(), coretimerRemainTime);
#else
#errro    
#endif
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
#if defined PIC32MM
	if (IEC0bits.CTIE){
		CORETIMER_DisableInterrupt();
		printf("stop timer interrupt.\r\n");
	}else{
		CORETIMER_Initialize();
		printf("Start timer interrupt.\r\n");
	}
#elif defined PIC32MK_MCJ
	if (T2CON & _T2CON_ON_MASK){
		TMR2_Stop();
		printf("stop timer.\r\n");
	}else{
		TMR2_Start();
		printf("Start timer.\r\n");
	}
#else
 #error
#endif
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
static bool bCurrentControl;
void changePwmMode(){
    bCurrentControl = !bCurrentControl;
	printf("PWM mode is %s\r\n", bCurrentControl ? "current" : "PWM");
}
void selectMotor(){
	motorCh++;
	if (motorCh >= NMOTOR) motorCh = 0;
	printf("Select motor %d. pww is %d\r\n", motorCh, pwm[motorCh]);
}
void pwmUp(){
//	if (pwm[motorCh] < 10) pwm[motorCh] ++;
	if (pwm[motorCh] < SDEC_ONE) pwm[motorCh] ++;
	printf("Set pwm %d to motor %d \r\n", pwm[motorCh], motorCh);
#ifdef PIC32MK_MCJ
    setPwm2(motorCh, pwm[motorCh] * (SDEC_ONE/50), bCurrentControl);
#else
    setPwm(motorCh, pwm[motorCh] * (SDEC_ONE/50));
#endif    
}
void pwmDown(){
//	if (pwm[motorCh] > -10) pwm[motorCh] --;
	if (pwm[motorCh] > -SDEC_ONE) pwm[motorCh] --;
	printf("Set pwm %d to motor %d \r\n", pwm[motorCh], motorCh);
#ifdef PIC32MK_MCJ
	setPwm2(motorCh, pwm[motorCh] * (SDEC_ONE/50), bCurrentControl);
#else
	setPwm(motorCh, pwm[motorCh] * (SDEC_ONE/50));
#endif
}
void showPwm(){
#ifdef PIC32MK_MCJ    
	printf("Pwm ct:%d \r\n", PMTMR);
#endif
}

#ifdef PIC32MM
static unsigned short useRx = 0;
void enableRx(){
    useRx = 0xFFFF;
#ifdef BOARD3_SEPARATE
    printf("RX enabled. Baud rate will be changed into 1200 bps.\r\n");
#else
    printf("RX enabled.\r\n");
#endif
    U1MODE = (0x8008 & ~(1<<15)); // disabling UART ON bit  
    ANSELB = 0x300F; //U1RX=AN10=RB15, U1TX=RB14, AN8=RB13, AN7=RB12, RB3210=AN11 AN4 AN3 AN2
#ifdef BOARD3_SEPARATE
    U1BRG = 0x1387; // 1200bps 1uF requires 1ms.
#endif
    U1STASET = _U1STA_URXEN_MASK;   //  Enable RX
    U1MODESET = _U1MODE_ON_MASK;	//  Enable UART ON bit
}
void disableRx(){
    useRx = 0;
#ifdef BOARD3_SEPARATE
    printf("RX disabled. Baud rate will be changed into 3000000 bps.\r\n");
    while(!U1STAbits.TRMT) monOut();
#else
    printf("RX enabled.\r\n");
#endif
    U1MODE = (0x8008 & ~(1<<15)); // disabling UART ON bit  
    ANSELB = 0xB00F; //AN10=RB15, U1TX=RB14, AN8=RB13, AN7=RB12, RB3210=AN11 AN4 AN3 AN2
#ifdef BOARD3_SEPARATE
    U1BRG = 0x1;    // 3000000
#endif
    U1STASET = _U1STA_URXEN_MASK;   //  Enable RX
    U1MODESET = _U1MODE_ON_MASK;	//  Enable UART ON bit
}
extern unsigned long spiPwmGpBackup;
void printGp(){
#ifdef PIC32MM
    printf("spiPwmGpBackup = %x.\r\n", (int)spiPwmGpBackup);
#endif
}
#endif

void nvmWriteTest(){
    NvData data;
    NVMRead(&data);
    int i;
    data.boardId ++;
    if (data.boardId > 7) data.boardId = 1;
    /*
    printf("Before Write:\r\n");
    for(i=0; i<sizeof(data); ++i){
        printf("%02x ", ((unsigned char*)&data)[i]);
        if (i%16 == 15) printf("\r\n");
        else if (i%8 == 7) printf(" ");
    }
    printf("\r\n");
    */
    i = NVMWrite(&data);
    printf("NVMWrite() returns %d\r\n", i);
}
void nvmReadTest(){
    NvData data;
    int i;
    NVMRead(&data);
    printf("NVM Read:\r\n");
    for(i=0; i<sizeof(data); ++i){
        printf("%02x ", ((unsigned char*)&data)[i]);
        if (i%16 == 15) printf("\r\n");
        else if (i%8 == 7) printf(" ");
    }
    printf("\r\n");
}
void readLine(char* buf, int len){
	int cur = 0;
    while(cur+1 < len){
        monOut();
		if (UMSTAbits.URXDA){
            buf[cur] = UMRXREG;
            if (buf[cur] == '\r' || buf[cur] == '\n'){
                break;
            }else{
                printf("%c", buf[cur]);
            }
            cur ++;
        }
	}
    buf[cur] = 0;
}
#ifdef PIC32MM
#define ADCCON1 AD1CON1
#endif
void readAddress(){
    printf("Input offset:");
    char adr[80];
    readLine(adr, sizeof(adr));
    int delta = strtol(adr, NULL, 0)*4;
    volatile unsigned int* ptr = &ADCCON1 + delta;
    unsigned int val1 = ptr[0];
    unsigned int val2 = ptr[4];
    unsigned int val3 = ptr[8];
    unsigned int val4 = ptr[12];
    int adrLow = (unsigned int)ptr & 0xFFFF;
    printf("\r\nAdr:%x  Value = 0x%x 0x%x 0x%x 0x%x\r\n", adrLow, val1, val2, val3, val4);
}
void writeAddress(){
    printf("Input offset:");
    char buf[80];
    readLine(buf, sizeof(buf));
    int delta = strtol(buf, NULL, 0)*4;
    volatile unsigned int* ptr = &ADCCON1 + delta;
    int adrLow = (unsigned int)ptr & 0xFFFF;
    unsigned int val1 = ptr[0];
    printf("\r\nAdr:%x  Value = 0x%x\r\n", adrLow, val1);
    
    printf("Input value:");
    readLine(buf, sizeof(buf));
    unsigned int value = strtol(buf, NULL, 0);
    ptr[0] = value;
    printf("\r\nAdr:%x  Value: 0x%x -> 0x%x\r\n", adrLow, val1, value);
}
struct MonitorFunc monitors[] = {
	{'a', "Show all A/D value", showAD, true},
	{'A', "Show A/D value in motor order", showADInMotorOrder, true},
	{'r', "Show motor rotation", showMotorRotation, true},
	{'c', "Show control status", showControlStatus, true},
	{'C', "Show control timer", showControlTimer, true},
	{'U', "show uart status", showUartState, true},
    {'R', "read register", readAddress, false},
    {'W', "write register", writeAddress, false},
	{'L', "Log level up", logLevelUp, false},
	{'l', "Log level down", logLevelDown, false},
	{'s', "toggle control timer", toggleControlTimer, false},
	{'m', "Select motor", selectMotor, false},
	{'u', "Pwm up", pwmUp, false},
	{'d', "Pwm down", pwmDown, false},
    {'p', "pwm mode", changePwmMode, false},
	{'w', "Pwm status", showPwm, true},
#ifdef PIC32MM
	{'g', "Print GP", printGp, true},
#endif
	{'N', "Write NVM", nvmWriteTest, false},
	{'n', "Read NVM", nvmReadTest, false},
#ifdef PIC32MM
	{'E', "End monitor", disableRx, false},
#endif
};
void showHelp(){
	int i;
	for(i=0; i<sizeof(monitors)/sizeof(monitors[0]); ++i){
		printf("%c: %s %c\r\n", monitors[i].ch, monitors[i].desc, monitors[i].callAgain ? 'R':' ');
        while(!U1STAbits.TRMT) monOut();
	}
}

void monitor(){
	static int ch = 0;
	bool bHit = false;
	int i;
#if  defined PIC32MM && (!defined BOARD1_MOTORDRIVER && !defined USE_MONITOR_RX)
    //  Enable U1RX when break signal is sent.
    if (NCURRENT == 4 && useRx != 0xFFFF){
        if (useRx < 10){
            if (currentSense[1] > 3000){
                useRx ++;
            }
        }else if (useRx < 20){
            if (currentSense[1] < 2000) useRx ++;
        }else{
            enableRx();
        }
    }
#endif
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
