#pragma once

#include "VCEdit.h"
#include "../../PCRoboKey/CommandId.cs"
#define _COMMANDID_CS
#include "../../PIC/env.h"
#include "../../PIC/decimal.h"
#include "../../PIC/commandCommon.h"

enum BD0_PARAM {
	BD0_MODEL_NUMBER = -1,
	BD0_NTARGET = 0,
	BD0_NMOTOR = 0,
	BD0_NFORCE = 0,
};

DEFINE_Packets(BD0)
