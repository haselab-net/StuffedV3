#include "module_srmovement.h"

static bool waitResponse = false;       // wair nOccupied after send one keyframe
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
        if (jsRobotState.movement.nOccupied[motorId] > MAX_NOCCUPIED) {
            duk_pop(ctx);
            return false;
        }
    }
    duk_pop(ctx);

    duk_get_prop_string(ctx, -1, "movementId");
    uint8_t movementId = duk_get_int(ctx, -1);
    duk_pop(ctx);
    if (jsRobotState.movement.isPaused(movementId)) return false;

    return true;
}

static duk_ret_t send(duk_context *ctx) {
    duk_get_prop_string(ctx, -1, "movementCommandId");
    uint8_t movementCommandId = duk_get_int(ctx, -1);
    duk_pop(ctx);

    switch (movementCommandId)
    {
    case CI_M_ADD_KEYFRAME:
        if (!canAddKeyframe(ctx)) {
            duk_pop(ctx);
            duk_push_boolean(ctx, false);
            return 1;
        }
        waitResponse = true;
        break;
    case CI_M_PAUSE_MOV: {
        duk_get_prop_string(ctx, -1, "movementId");
        uint8_t movementId = duk_get_int(ctx, -1);
        duk_pop(ctx);
        jsRobotState.movement.pause(movementId);
        break;
    }
    case CI_M_RESUME_MOV: {
        duk_get_prop_string(ctx, -1, "movementId");
        uint8_t movementId = duk_get_int(ctx, -1);
        duk_pop(ctx);
        jsRobotState.movement.resume(movementId);
        break;
    }
    default:
        break;
    }

    duk_pop(ctx);
    duk_push_boolean(ctx, true);
    return 1;
}

void onSrMovementReceiveCIUMovement(const void *movementData) {
    const void* payload = movementData;

    uint8_t movementCommandId;
    popPayloadNum(payload, movementCommandId);

    switch (movementCommandId)
    {
    case CIU_MOVEMENT:
    case CI_M_QUERY:
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