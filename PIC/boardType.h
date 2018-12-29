#pragma once
#include "commandCommon.h"

#if 0
#define BOARD1_MOTORDRIVER		//	1st board without WROOM
#elif 0
#define BOARD2_COMBINATION		//	2nd board with WROOM
#else
#define BOARD3_SEPARATE         //	3nd board WROOM only / pic only New
#endif

#ifndef WROOM

#if defined BOARD1_MOTORDRIVER
 CHOOSE_BoardInfo(B1F);	//	B1M or B1F
 #define BOARD_ID	1
#elif defined BOARD2_COMBINATION
 CHOOSE_BoardInfo(B2M);	//	B2M or B2F
 #define BOARD_ID	7
#elif defined BOARD3_SEPARATE
 CHOOSE_BoardInfo(B3M);	//	B3M or B3F
 #define BOARD_ID	4 
#endif

#endif
