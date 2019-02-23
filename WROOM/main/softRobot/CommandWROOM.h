#pragma once
#include "../../../PIC/env.h"

#ifndef _COMMANDID_CS
#include "../../../PCRoboKey/CommandId.cs"
#define _COMMANDID_CS
#endif

#include "../../../PIC/fixed.h"
#include "../../../PIC/commandCommon.h"

enum BD0_PARAM {
	BD0_MODEL_NUMBER = -1,
	BD0_NTARGET = 12,
	BD0_NMOTOR = 3,
#ifndef _WIN32
	BD0_NCURRENT = 0,
	BD0_NFORCE = 0,
#else
	BD0_NCURRENT = 1,
	BD0_NFORCE = 1,
#endif
};
DEFINE_Packets(BD0)

CHOOSE_BoardInfo(BD0);	//	B2M or B2F
#define BOARD_ID 0xFF 