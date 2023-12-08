#ifndef NVM_H
#define NVM_H
#include "control.h"

//  NVM (Flash Program Memory) Utilities
unsigned int NVMUnlock (unsigned int nvmop);
unsigned int NVMErasePage(unsigned int address);
unsigned int NVMWriteWord(void* address, unsigned int data_l, unsigned int data_h);
void NVMUnprotectPFM(unsigned int address);

//  page size = 512 x 32bit words = 2048 bytes = 0x800 bytes
//  row size = 64 x 32bit words = 256 bytes = 0x100 bytes
//  64kb = 0x0000-0xFFFF flash. The last page is 0xE800-0xFFFF
//  Virtual memory addrsss starts from 0x9D00:E800.
//  Non volatile memory data structre. Add variable here to add nv variables.
typedef struct {
    unsigned char boardId;                  //  1
    unsigned char pad[1];                   //  2
    unsigned short encoder;                 //  4       flag 1:QE 0:ADC
    unsigned long baudrate[2];              // 12
    struct PdParam param;                   // 36       2x3x4 = 24 
    struct TorqueLimit torque;              // 52       2x2x4 = 16
    MotorHeatLimit heat;                    // 68       2x2x4 = 16
    unsigned short pwmResolution;           // 70       2
} __attribute__((__packed__)) NvData;

#ifdef PIC
#ifdef PIC32MM
#define NVPAGESIZE  0x800
#define NVROWSIZE   0x100
#elif defined PIC32MK_MCJ
#define NVPAGESIZE  0x1000
#define NVROWSIZE   0x200
#else
#error
#endif
extern const struct NvPageData theNvPage;
#define PNVDATA     ((NvData*)(void*)&theNvPage)
#define NVPAGE  ((unsigned int)PNVDATA)
unsigned int NVMWrite(NvData* p);
void NVMRead(NvData* p);
#endif

#endif