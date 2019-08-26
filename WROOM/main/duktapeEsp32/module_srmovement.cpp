#include "module_srmovement.h"
#include "../softRobot/Movement.h"

static bool waitResponse = false;       // wait nOccupied after send one keyframe
static uint16_t MAX_MOTOR_KEYFRAME_COUNT = 256;
static uint8_t MAX_MOVEMENT_KEYFRAME_COUNT = 32;

static const char* LOG_TAG = "module_srmovement";

static bool canAddKeyframe(duk_context * ctx) {
    if (waitResponse) return false;

    duk_get_prop_string(ctx, -1, "motorCount");
    uint8_t motorCount = duk_get_int(ctx, -1);
    duk_pop(ctx);

    duk_get_prop_string(ctx, -1, "motorId");
    for (int i=0; i<motorCount; i++) {
        duk_get_prop_index(ctx, -1, i);
        uint8_t motorId = duk_get_int(ctx, -1);
        duk_pop(ctx);
        if (motorId >= allBoards.GetNTotalMotor()) {
            duk_pop(ctx);
            ESP_LOGE(LOG_TAG, "canAddKeyframe: motorId larger than motor count");
            return false;
        }
    }
    duk_pop(ctx);

    // validate total count of keyframes
    uint16_t totalMotorKeyframes = 0;
    for (int i = 0; i < allBoards.GetNTotalMotor(); i++) totalMotorKeyframes += motorHeads[i].nOccupied;
    if (totalMotorKeyframes >= MAX_MOTOR_KEYFRAME_COUNT) return false;

    // validate count of keyframes of movement
    duk_get_prop_string(ctx, -1, "movementId");
    uint8_t movementId = duk_get_int(ctx, -1);
    duk_pop(ctx);
    vector<MovementInfoNode>::iterator it = getMovementInfo(movementId);
    if (it != movementInfos.end() && it->keyframeCount >= MAX_MOVEMENT_KEYFRAME_COUNT) return false;

    // check if paused
    jsRobotState.read_lock();
    if (jsRobotState.movement.isPaused(movementId)) {
        jsRobotState.read_unlock();
        return false;
    }
    jsRobotState.read_unlock();

    return true;
}

static duk_ret_t send(duk_context *ctx) {
    // .. command

    duk_get_prop_string(ctx, -1, "movementCommandId");
    uint8_t movementCommandId = duk_get_int(ctx, -1);
    duk_pop(ctx);

    switch (movementCommandId)
    {
    case CI_M_ADD_KEYFRAME:
        if (!canAddKeyframe(ctx)) {
            duk_pop(ctx);
            duk_push_false(ctx);
            return 1;
        }
        waitResponse = true;
        break;
    case CI_M_PAUSE_MOV: {
        duk_get_prop_string(ctx, -1, "movementId");
        uint8_t movementId = duk_get_int(ctx, -1);
        duk_pop(ctx);
        jsRobotState.write_lock();
        jsRobotState.movement.pause(movementId);
        jsRobotState.write_unlock();
        break;
    }
    case CI_M_RESUME_MOV: {
        duk_get_prop_string(ctx, -1, "movementId");
        uint8_t movementId = duk_get_int(ctx, -1);
        duk_pop(ctx);
        jsRobotState.write_lock();
        jsRobotState.movement.resume(movementId);
        jsRobotState.write_unlock();
        break;
    }
    default:
        break;
    }

    setMovement(ctx);
    duk_pop(ctx);

    duk_push_true(ctx);

    return 1;
}

// export function isMovementPlaying(movement: Movement): boolean {
static duk_ret_t isMovementPlaying(duk_context* ctx) {
    // .. movement

    duk_get_prop_string(ctx, -1, "movementId");
    duk_int_t movementId = duk_get_int(ctx, -1);
    duk_pop(ctx);
    // .. movement

    duk_pop(ctx);
    // ..

    vector<MovementInfoNode>::iterator it = getMovementInfo(movementId);
    if (it == movementInfos.end()) duk_push_false(ctx);
    else {
        jsRobotState.read_lock();
        bool paused = jsRobotState.movement.isPaused(movementId);
        jsRobotState.read_unlock();
        if (paused) duk_push_false(ctx);
        else duk_push_true(ctx);
    }

    return 1;
}

void onSrMovementReceiveCIUMovement(const void *movementData) {
    const void* payload = movementData;

    uint8_t movementCommandId;
    popPayloadNum(payload, movementCommandId);

    switch (movementCommandId)
    {
    case CI_M_ADD_KEYFRAME:
        waitResponse = false;
        break;
    
    default:
        break;
    }
}

extern "C" duk_ret_t ModuleSRMovement(duk_context *ctx) {
    waitResponse = false;

    ADD_FUNCTION("send", send, 1);
    ADD_FUNCTION("isMovementPlaying", isMovementPlaying, 1);

    return 0;
}