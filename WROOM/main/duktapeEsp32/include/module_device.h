#ifndef MAIN_INCLUDE_MODULE_DEVICE_H_
#define MAIN_INCLUDE_MODULE_DEVICE_H_

#ifdef __cplusplus

#include <vector>
#include "../../softRobot/AllBoards.h"
#include <freertos/freertos.h>
#include <freertos/semphr.h>
using namespace std;

class JSMovementState {
    public:
    vector<uint8_t> nOccupied;
    vector<uint8_t> pausedMovements;

    JSMovementState(AllBoards& allBoards);

    void pause(uint8_t movementId);
    void resume(uint8_t movementId);
    bool isPaused(uint8_t movementId);
};

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

class JSRobotState {
    public:
    vector<struct JSMotorState> motor;
    vector<int16_t> current;
    vector<int16_t> force;
    vector<int16_t> touch;
    class JSMovementState movement;

    JSRobotState(AllBoards& allBoards);

    void read_lock();
    void read_unlock();
    void write_lock();
    void write_unlock();

    private:
    xSemaphoreHandle readSemaphore;
    xSemaphoreHandle writeSemaphore;
};
extern JSRobotState jsRobotState;

extern "C" {
#endif

void initModuleDevice();

#ifdef __cplusplus
}
#endif


#endif /* MAIN_INCLUDE_MODULE_DEVICE_H_ */