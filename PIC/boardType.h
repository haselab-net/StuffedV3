#pragma once
#include "commandCommon.h"

#if 0
#define BOARD1_MOTORDRIVER		//	first board without WROOM
#else
#define BOARD2_COMBINATION		//	second board with WROOM
#endif

#if defined BOARD1_MOTORDRIVER
CHOOSE_BoardInfo(B1F);	//	B1M or B1F
#elif defined BOARD2_COMBINATION
CHOOSE_BoardInfo(B2M);	//	B2M or B2F
#endif

#define BOARD_ID	0
