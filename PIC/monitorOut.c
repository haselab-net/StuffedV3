#include "env.h"
#include "embeddedFramework.h"

#ifdef PIC32MM

#ifndef MODULETEST
static char mon_buffer[512];
static int wp=0;
static int rp=0;
bool monOut(){
    if (rp != wp && !UMSTAbits.UTXBF){
		UMTXREG = mon_buffer[rp];
		if (rp < sizeof(mon_buffer)-1) rp++;
		else rp = 0;
	}
    return rp != wp;    //  if remain return true
}
int monWaiting(){
    int rv = rp - wp;
    if (rv < 0) rv += sizeof(mon_buffer); 
    if (rv >= sizeof(mon_buffer)) rv -= sizeof(mon_buffer); 
    return rv;
}
void _mon_putc(char c) {
	mon_buffer[wp] = c;
	if (wp < sizeof(mon_buffer)-1) wp++;
	else wp = 0;
	monOut();
}
#else
void _mon_putc(char c) {
    while(UMSTAbits.TRMT == 0);  
    UMTXREG = c;        
}
#endif

#elif defined PIC32MK_MCJ

bool monOut(){
    return false;
}
int monWaiting(){ return 0; }

#else
#error
#endif
