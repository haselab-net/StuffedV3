#include "env.h"
#include "nvm.h"
#include "boardType.h"
#include <assert.h>
#include <string.h>

#ifdef PIC32MK_MCJ
#include "definitions.h"                // SYS function prototypes
#endif

struct NvPageData{
    NvData nvData;
    char nvFill[NVPAGESIZE-sizeof(NvData)];
}__attribute__((__packed__));

#if BOARD_TYPE==BT_B3F || BOARD_TYPE==BT_B2F || BOARD_TYPE==BT_B1F
 #define EL4(x)  
 #define EL5678(x)
#elif BOARD_TYPE==BT_B3M || BOARD_TYPE==BT_B2M || BOARD_TYPE==BT_B1M
 #define EL4(x) x
 #define EL5678(x)
#elif BOARD_TYPE==BT_B5M
 #define EL4(x) x
 #define EL5678(a, b, c, d) a,b,c,d
#else
 #error BORAD_TYPE must be specified.
#endif

const struct NvPageData __attribute__((aligned(NVPAGESIZE))) theNvPage = {
    {
        BOARD_ID,   //  boardID
        {0},        //  pad
        0x0,          //  encoder flags for each motor (1:QE=encoder, 0:ADC=magnet sensor)        
        {2000000, 3000000},    //  2MBPS for command, 3MBPS for monitor
        {   //  PDParam
            {PDPARAM_K, PDPARAM_K, PDPARAM_K, EL4(PDPARAM_K), EL5678(PDPARAM_K, PDPARAM_K, PDPARAM_K, PDPARAM_K)},   //k
            {PDPARAM_B, PDPARAM_B, PDPARAM_B, EL4(PDPARAM_B), EL5678(PDPARAM_B, PDPARAM_B, PDPARAM_B, PDPARAM_B)},   //b
            {PDPARAM_A, PDPARAM_A, PDPARAM_A, EL4(PDPARAM_A), EL5678(PDPARAM_A, PDPARAM_A, PDPARAM_A, PDPARAM_A)},   //a
        },
        {//  TorqueLimit
            {-SDEC_ONE, -SDEC_ONE, -SDEC_ONE, EL4(-SDEC_ONE), EL5678(-SDEC_ONE, -SDEC_ONE, -SDEC_ONE, -SDEC_ONE)},   //  min
            {SDEC_ONE, SDEC_ONE, SDEC_ONE, EL4(SDEC_ONE), EL5678(SDEC_ONE, SDEC_ONE, SDEC_ONE, SDEC_ONE)},       //  max   
        },
        {//  MotorHeatLimit       
            {MOTOR_HEAT_LIMIT/MOTOR_HEAT_RELEASE, MOTOR_HEAT_LIMIT/MOTOR_HEAT_RELEASE, MOTOR_HEAT_LIMIT/MOTOR_HEAT_RELEASE, EL4(MOTOR_HEAT_LIMIT/MOTOR_HEAT_RELEASE),
                    EL5678(MOTOR_HEAT_LIMIT/MOTOR_HEAT_RELEASE, MOTOR_HEAT_LIMIT/MOTOR_HEAT_RELEASE, MOTOR_HEAT_LIMIT/MOTOR_HEAT_RELEASE, MOTOR_HEAT_LIMIT/MOTOR_HEAT_RELEASE)
            },   //  SDEC limit
            {MOTOR_HEAT_RELEASE, MOTOR_HEAT_RELEASE, MOTOR_HEAT_RELEASE, EL4(MOTOR_HEAT_RELEASE),
                MOTOR_HEAT_RELEASE, MOTOR_HEAT_RELEASE, MOTOR_HEAT_RELEASE, MOTOR_HEAT_RELEASE}    // SDEC release
        },
    }
};

#ifdef PIC32MM___
/*  Page size = 512 x 32 bit words = 2048 bytes = 0x800 bytes
 *  64kB flash = 9d00_0000 - 9d00_FFFF
 *  program 0000-a97d
 *  The last page in Boot Flash Memory contains the debug page.
 */
unsigned int NVMUnlock (unsigned int nvmop){
	unsigned int status;
	// Suspend or Disable all Interrupts
    asm volatile ("di %0" : "=r" (status));
	// Enable Flash Write/Erase Operations and Select
	// Flash operation to perform
	NVMCON = nvmop;
	// Write Keys
	NVMKEY = 0xAA996655;
	NVMKEY = 0x556699AA;
	// Start the operation using the Set Register
	NVMCONSET = 0x8000;
	// Wait for operation to complete
	while (NVMCON & 0x8000);
	// Restore Interrupts
	if (status & 0x00000001){
		asm volatile ("ei");
	}else{
		asm volatile ("di");
    }
	// Disable NVM write enable
	NVMCONCLR = 0x0004000;
	if (NVMCON & 0x3000){
        printf("NVMUnlock NVMCON: %x\r\n", NVMCON);
    }
    // Return WRERR and LVDERR Error Status Bits
	return (NVMCON & 0x3000);
}
unsigned int NVMErasePage(unsigned int address){
    unsigned int res;
    // Load address to program into NVMADDR register
    NVMADDR = (address & 0x0FFFFFFF) | 0x10000000;
    // Unlock and Erase page
    res = NVMUnlock(0x4004);   //    4:WREN,0,0,4:erase page
    // Return Result
    return res;
}
unsigned int NVMWriteWord (void* address, unsigned int data_l, unsigned int data_h)
{
    unsigned int res;
    // Load data into NVMDATA register
    NVMDATA0 = data_l;
    NVMDATA1 = data_h;
    // Load address to program into NVMADDR register
    NVMADDR = ((unsigned int) address & 0x0FFFFFFF) | 0x10000000;
    // Unlock and Write Word
    res = NVMUnlock(0x4002);   //    4:WREN,0,0,2:double word write
    // Return Result
    return res;
}
void NVMUnprotectPFM(unsigned int address){
	unsigned int status;
	// Suspend or Disable all Interrupts
    asm volatile ("di %0" : "=r" (status));

	// Write Keys
	NVMKEY = 0xAA996655;
	NVMKEY = 0x556699AA;
    NVMPWP = 0x80000000 + (address & 0xFFFF);

	if (status & 0x00000001){
		asm volatile ("ei");
	}else{
		asm volatile ("di");
    }
}
unsigned int NVMWrite(NvData* data){
    unsigned int cur, rv=0;
    assert(sizeof(NvData) < NVPAGESIZE);
    cur = (unsigned int)data;
    NVMUnprotectPFM(NVPAGE - NVPAGESIZE);
    NVMErasePage(NVPAGE);
    NVMADDR = ((unsigned int) NVPAGE & 0x0FFFFFFF) | 0x10000000;
    while(cur - ((unsigned int)data) < sizeof(NvData)){
        NVMDATA0 = ((unsigned int*)(cur))[0];
        NVMDATA1 = ((unsigned int*)(cur))[1];
        rv |= NVMUnlock(0x4002);  //  two words programming
        cur += sizeof(int)*2;
        NVMADDR += sizeof(int)*2;
    }
    return rv;
}
#else
unsigned int NVMWrite(NvData* data){
    assert(sizeof(NvData) < NVPAGESIZE);
    NVM_PageErase(NVPAGE);    
    while(NVM_IsBusy());
    int offset = 0;
    unsigned int rv = 0;

    while(offset < sizeof(NvData)){
        rv = NVM_WordWrite(*(unsigned int*)( ((char*)data)+offset ), NVPAGE+offset);
        while(NVM_IsBusy());
        //offset += NVM_FLASH_ROWSIZE;
        offset += 4;
        //printf("rv: %d offset%x", rv, offset);
    }
    return rv;
}


#endif

void NVMRead(NvData* p){
    assert(sizeof(NvData) < NVPAGESIZE);
    memcpy(p, PNVDATA, sizeof(NvData));
}
