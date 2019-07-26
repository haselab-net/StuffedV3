#include "module_srmovement.h"

static bool waitResponse = false;       // wait nOccupied after send one keyframe
static uint8_t MAX_NOCCUPIED = 5;

static char* LOG_TAG = "module_srmovement";

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
        jsRobotState.read_lock();
        if (jsRobotState.movement.nOccupied[motorId] >= MAX_NOCCUPIED) {
            duk_pop(ctx);
            return false;
        }
        jsRobotState.read_unlock();
    }
    duk_pop(ctx);
    printf("--- pass nOccupied \n");

    duk_get_prop_string(ctx, -1, "movementId");
    uint8_t movementId = duk_get_int(ctx, -1);
    duk_pop(ctx);
    jsRobotState.read_lock();
    if (jsRobotState.movement.isPaused(movementId)) return false;
    jsRobotState.read_unlock();
    printf("--- pass isPaused \n");

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

    return 0;
}