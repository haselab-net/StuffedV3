#pragma once
#include "env.h"

#ifdef PIC32MK_MCJ
    #define BOARD5
#else
    #if 0
     #define BOARD1_MOTORDRIVER		//	1st board without WROOM
    #elif 0
     #define BOARD2_COMBINATION		//	2nd board with WROOM
    #elif 0
     #define BOARD3_SEPARATE         //	3nd board WROOM only / pic only New
    #elif 1
     #define BOARD4                  //	4th board WROOM Updated (new pin assing) and current read fast RX PIC board
    #endif
#endif

#ifndef WROOM
#define BT_B1M 1
#define BT_B1F 2
#define BT_B2M 3
#define BT_B2F 4
#define BT_B3M 5
#define BT_B3F 6
#define BT_B5M 7


#if defined BOARD1_MOTORDRIVER
 #define BOARD_TYPE BT_B1F //	B1M or B1F
#elif defined BOARD2_COMBINATION
 #define BOARD_TYPE BT_B2M	//	B2M or B2F
#elif defined BOARD3_SEPARATE
 #define BOARD_TYPE BT_B3M	//	B3M or B3F
#elif defined BOARD4
 #define BOARD_TYPE BT_B3M	//	B3M or B3F
#elif defined BOARD5
 #define BOARD_TYPE BT_B5M  
#endif
 
#define BOARD_ID	1

 
#endif
