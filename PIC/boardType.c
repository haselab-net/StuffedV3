#include "boardType.h"

#ifndef WROOM

#if defined BOARD1_MOTORDRIVER
 CHOOSE_BoardInfoImpl(B1F);	//	B1M or B1F
#elif defined BOARD2_COMBINATION
 CHOOSE_BoardInfoImpl(B2M);	//	B2M or B2F
#elif defined BOARD3_SEPARATE
 CHOOSE_BoardInfoImpl(B3M);	//	B3M or B3F
#elif defined BOARD4
 CHOOSE_BoardInfoImpl(B3M);	//	B3M or B3F
#endif

#endif
