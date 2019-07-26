#include "module_device.h"

JSMovementState::JSMovementState(AllBoards& allBoards) {
    nOccupied.resize(allBoards.GetNTotalMotor(), 0);
}

void JSMovementState::pause(uint8_t movementId) {
    for (int i=0; i<pausedMovements.size(); i++) {
        if (pausedMovements[i] == movementId) return;
    }
    pausedMovements.push_back(movementId);
}

void JSMovementState::resume(uint8_t movementId) {
    for (int i=0; i<pausedMovements.size(); i++) {
        if (pausedMovements[i] == movementId) {
            pausedMovements.erase(pausedMovements.begin() + i);
            return;
        }
    }
}

bool JSMovementState::isPaused(uint8_t movementId) {
    for (int i=0; i<pausedMovements.size(); i++) {
        if (pausedMovements[i] == movementId) return true;
    }
    return false;
}

JSRobotState jsRobotState(allBoards);

JSRobotState::JSRobotState(AllBoards& allBoards) : movement(allBoards)  {
    struct JSMotorState template_motor_state = {
        0, 0, -5000, 5000, 4096, 2048, 0, -1024, 1024
    };
    motor.resize(allBoards.GetNTotalMotor(), template_motor_state);
    current.resize(allBoards.GetNTotalCurrent(), 0);
    force.resize(allBoards.GetNTotalForce(), 0);
    touch.resize(allBoards.GetNTotalTouch(), 0);

    readSemaphore = xSemaphoreCreateMutex();
    writeSemaphore = xSemaphoreCreateMutex();
}

void JSRobotState::read_lock() {
    //xSemaphoreTake(writeSemaphore, portMAX_DELAY);
}
void JSRobotState::read_unlock() {
    //xSemaphoreGive(writeSemaphore);
}
void JSRobotState::write_lock() {
    //xSemaphoreTake(writeSemaphore, portMAX_DELAY);
    //xSemaphoreTake(readSemaphore, portMAX_DELAY);
}
void JSRobotState::write_unlock() {
    //xSemaphoreGive(readSemaphore);
    //xSemaphoreGive(writeSemaphore);
}

extern "C" void initModuleDevice() {
    jsRobotState = JSRobotState(allBoards);
}