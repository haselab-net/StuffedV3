#ifndef MAIN_INCLUDE_MODULE_DEVICE_H_
#define MAIN_INCLUDE_MODULE_DEVICE_H_

#ifdef __cplusplus

#include <vector>
#include "../../softRobot/AllBoards.h"
using namespace std;

struct JSMotorState {
    int16_t pose;
    int16_t velocity;
    int16_t lengthMin;
    int16_t lengthMax;
    int16_t controlK;
    int16_t controlB;
    int16_t controlA;
    int16_t torqueMin;
    int16_t torqueMax; 
};

class RobotState {
    public:
    vector<struct JSMotorState> motor;
    vector<int16_t> current;
    vector<int16_t> force;
    vector<int16_t> touch;

    RobotState(AllBoards& allBoards);
};
extern RobotState robotState;

extern "C" {
#endif

void initModuleDevice();

#ifdef __cplusplus
}
#endif


#endif /* MAIN_INCLUDE_MODULE_DEVICE_H_ */