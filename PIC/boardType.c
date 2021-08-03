#include "boardType.h"
#include "command.h"

#ifndef WROOM


#if BOARD_TYPE==BT_B1M
 CHOOSE_BoardInfoImpl(B1M)
#elif BOARD_TYPE == BT_B1F
 CHOOSE_BoardInfoImpl(B1F)
#elif BOARD_TYPE == BT_B2M
 CHOOSE_BoardInfoImpl(B2M)
#elif BOARD_TYPE == BT_B2F
 CHOOSE_BoardInfoImpl(B2F)
#elif BOARD_TYPE == BT_B3M
 CHOOSE_BoardInfoImpl(B3M)
#elif BOARD_TYPE == BT_B3F
 CHOOSE_BoardInfoImpl(B3F)
#else
#error BORAD_TYPE is wrong.
#endif

#endif
