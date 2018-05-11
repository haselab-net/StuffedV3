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
void monitor(){
	static int ch = 0;
	int i;
	if (UMSTAbits.URXDA){
		ch = UMRXREG;
	}
	if (ch != ' ' && ch != 0){
        while(monWaiting()) monOut()    ;
        //printf("%c", ch);
    }
	switch(ch){
#if 0	//	Dangerous for full circuit.
		case 'S':
			SPI2BUF = 0xFF00FF00;
			break;
		case 'O':
			outTest(1);
			ch = 0;
			break;
		case 'o':
			outTest(0);
			ch = 0;
			break;
		case 'w':
			pwmTest2();
			printf(" pwm test 2.\r\n");
			ch = 0;
			break;				
		case 'p':
			pwmTest(0);
			ch = 0;
			break;
		case 'P':
			pwmTest(1);
			ch = 0;
			break;
#endif
		case 'a':	//	ad converter
			printf("ad");
			for(i=0; i<16; ++i) printf(" %x", *(&ADC1BUF0 + 4*i));
			printf("\r\n");
			break;
		case 'A':	//	ad converter in motor order
			printf("Ad");
#if defined BOARD1_MOTORDRIVER
			printf(" %d %d ", ADC1BUF5, ADC1BUF2);
			printf(" %d %d ", ADC1BUF7, ADC1BUF6);
			printf(" %d %d ", ADC1BUF1, ADC1BUF0);
			printf(" %d %d\r\n", ADC1BUF4, ADC1BUF3);
#elif defined BOARD2_COMBINATION			
			printf(" %d %d ", ADC1BUF0, ADC1BUF1);
			printf(" %d %d ", ADC1BUF6, ADC1BUF7);
			printf(" %d %d ", ADC1BUF3, ADC1BUF9);
			printf(" %d %d\r\n", ADC1BUF10, ADC1BUF11);
#else
#error
#endif

			break;
		case 'c':{	//	control status
			static uint32_t ct;
			if (ct != controlCount){
				ct = controlCount;
				printf("ctrl\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\r\n", 
						motorState.pos[0], motorTarget.pos[0], motorState.vel[0], motorTarget.vel[0], 
						targets.write, targets.read, targets.tick, targets.buf[(targets.read+1)%NTARGET].period, ct);
			}
		}break;
		case 'C':
			printf("Core timer cur:%8x cmp:%8x remain:%5d\r\n", 
					_CP0_GET_COUNT(), _CP0_GET_COMPARE(), coretimerRemainTime);
			break;
		case 'l':
			logLevel ++;
			printf("log level = %d", logLevel);
			ch = 0;
			break;
		case 'L':
			logLevel --;
			printf("Log level = %d", logLevel);
			ch = 0;
			break;
		case 's':
			if (IEC0bits.CTIE){
				CORETIMER_DisableInterrupt();
				printf("stop timer interrupt.\r\n");
			}else{
				CORETIMER_Initialize();
				printf("Start timer interrupt.\r\n");
			}
			ch = 0;
			break;
		case 'u':
			printf("u1STA %8x\r\n", U1STA);
			ch = 0;
			break;
		case 'r':
			{
			printf("r");
			int i;
			for(i=0; i<NMOTOR; ++i){
				printf(" %i=%2.3f (%d,%d)", i, LDEC2DBL(motorState.pos[i]), 
						mcos[i], msin[i]);
			}
			printf("\r\n");
			}
			break;
			
		case ' ':
		case 0:	//	operation completed.
			break;
		default:
			printf(" not used\r\n");
			break;
	}
}
