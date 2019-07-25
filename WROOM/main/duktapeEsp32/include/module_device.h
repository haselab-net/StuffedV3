#ifndef MAIN_INCLUDE_MODULE_DEVICE_H_
#define MAIN_INCLUDE_MODULE_DEVICE_H_

#ifdef __cplusplus

#include <vector>
#include "../../softRobot/AllBoards.h"
using namespace std;
class RobotState {
    public:
    vector<int16_t> touch;

    RobotState(AllBoards& allBoards) {
        touch.resize(allBoards.GetNTotalTouch(), 0);
    }
};
extern RobotState robotState;

extern "C" {
#endif

void initModuleDevice();

#ifdef __cplusplus
}
#endif


#endif /* MAIN_INCLUDE_MODULE_DEVICE_H_ */