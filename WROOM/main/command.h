#pragma once

#include "../../PCRoboKey/CommandId.cs"
#define _COMMANDID_CS
#include "../../PIC/env.h"
#include "../../PIC/fixed.h"
#include "../../PIC/commandCommon.h"
#include "MotorDriver.h"

enum BD0_PARAM {
	BD0_MODEL_NUMBER = -1,
	BD0_NTARGET = 0xFF,
	BD0_NMOTOR = BoardInfo::NMOTOR,
	BD0_NFORCE = 0,
};
DEFINE_Packets(BD0)
