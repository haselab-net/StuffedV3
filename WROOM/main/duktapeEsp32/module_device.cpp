#include "module_device.h"

RobotState robotState(allBoards);

extern "C" void initModuleDevice() {
    robotState = RobotState(allBoards);
}