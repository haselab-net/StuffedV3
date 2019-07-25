#include "module_device.h"

RobotState robotState(allBoards);

RobotState::RobotState(AllBoards& allBoards)  {
    struct JSMotorState template_motor_state = {
        0, 0, -5000, 5000, 4096, 2048, 0, -1024, 1024
    };
    motor.resize(allBoards.GetNTotalMotor(), template_motor_state);
    current.resize(allBoards.GetNTotalCurrent(), 0);
    force.resize(allBoards.GetNTotalForce(), 0);
    touch.resize(allBoards.GetNTotalTouch(), 0);
}

extern "C" void initModuleDevice() {
    robotState = RobotState(allBoards);
}