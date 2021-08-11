#ifndef COMMAND_H
#define COMMAND_H
#include "env.h"
#include "commandCommon.h"
#include "boardType.h"
#include <stdbool.h>

#ifdef PIC

#if BOARD_TYPE == BT_B1M
 CHOOSE_BoardInfo(B1M)
#elif BOARD_TYPE == BT_B1F
 CHOOSE_BoardInfo(B1F)
#elif BOARD_TYPE == BT_B2M
 CHOOSE_BoardInfo(B2M)
#elif BOARD_TYPE == BT_B2F
 CHOOSE_BoardInfo(B2F)
#elif BOARD_TYPE == BT_B3M
 CHOOSE_BoardInfo(B3M)
#elif BOARD_TYPE == BT_B3F
 CHOOSE_BoardInfo(B3F)
#else
#error BORAD_TYPE is wrong.
#endif

#endif

void commandInit();
bool uartExecCommand();
typedef void ExecCommand();

#ifdef WROOM
void ExecCmd();
void ExecRet();
extern CommandPacket command;
extern ReturnPacket retPacket;
#endif


#ifndef WROOM
extern CommandPacket command;
extern ReturnPacket retPacket;
extern int cmdCur;
extern int cmdLen;
extern int retCur;
extern int retLen;
extern ExecCommand* execCommand[CI_NCOMMAND];
extern ExecCommand* returnCommand[CI_NCOMMAND];
extern unsigned char cmdPacketLens[MAXBOARDID+1][CI_NCOMMAND];
extern unsigned char boardId;
#endif

#endif
