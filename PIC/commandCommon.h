#ifndef _COMMAND_COMMON_H
#define _COMMAND_COMMON_H

#include "env.h"
#ifdef __XC32
#include "mcc_generated_files/mcc.h"
#endif
#ifndef _COMMANDID_CS
#define _COMMANDID_CS
#include "../PCRobokey/commandId.cs"
#endif

//extern unsigned char boardId;
extern enum CommandId commandId;
#include "CommandTemplate.h"

enum B1M_PARAM{
	B1M_MODEL_NUMBER = 1,
	B1M_NTARGET = 12,
    B1M_NMOTOR = 4,
    B1M_NFORCE = 0,
};
enum B1F_PARAM{
	B1F_MODEL_NUMBER = 2,
    B1F_NTARGET = 8,
    B1F_NMOTOR = 3,
    B1F_NFORCE = 2,
};

DEFINE_Packets(B1M)

DEFINE_Packets(B1F)


#endif
