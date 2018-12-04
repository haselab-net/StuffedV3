#pragma once

#include "esp_log.h"
#include "../PIC/decimal.h"
#include "TinyContainer.h"

class Robot{
    public:
    struct Motor{
        LDEC target;
        LDEC current;
        int iBoard;    //   index of the board
        int iMotor;    //   index of the motor in the board.
    }
    tiny::vector<Motor> motors;

    struct Keyframe{
        int period;
        tiny::vector<LDEC> targets;
    }
}
