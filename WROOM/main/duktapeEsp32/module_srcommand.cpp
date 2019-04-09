#include <stdio.h>
extern "C" {

#include <duktape.h>
#include "duktape_event.h"
#include "duktape_utils.h"
#include "module_srcommand.h"
}
#include "../softRobot/UdpCom.h"
#include "../softRobot/AllBoards.h"

static const char* Tag = "SRCmd";

////////////////////////////////////////////////////////
//////////////////////// send functions ////////////////
////////////////////////////////////////////////////////

// function requireBoardInfo();
// TODO

// function requireSensorInfo();
// TODO

// function setMotorDirect(data: {pose: number[], velocity: number[]});
static duk_ret_t setMotorDirect(duk_context* ctx) {
    // ... obj
    duk_require_object(ctx, -1);

    duk_get_prop_string(ctx, -1, "pose");
    // ... obj pose
    if (!duk_is_array(ctx, -1)) {
        duk_pop_2(ctx);
        return DUK_ERR_TYPE_ERROR;
    }
    size_t n0 = duk_get_length(ctx, -1);

    duk_get_prop_string(ctx, -2, "velocity");
    // ... obj pose velocity
    if (!duk_is_array(ctx, -1)) {
        duk_pop_3(ctx);
        return DUK_ERR_TYPE_ERROR;
    }
    size_t n1 = duk_get_length(ctx, -1);

    //  Prepare command
	UdpCmdPacket* cmd = udpCom.PrepareCommand(CI_DIRECT);
    if (!cmd) return DUK_ERR_ERROR;
    if (cmd->length != (2+n0+n1)*2) return DUK_ERR_TYPE_ERROR;

    // iterate pose
    for(int i=0; i<n0; i++){
        duk_get_prop_index(ctx, -2, i);
        cmd->data[i] = duk_get_int(ctx, -1);
        duk_pop(ctx);
    }
    // iterate velocity
    for(int i=0; i<n1; i++){
        duk_get_prop_index(ctx, -1, i);
        cmd->data[n0+i] = duk_get_int(ctx, -1);
        duk_pop(ctx);
    }
    //  send the packet
	udpCom.WriteCommand();

    // ... obj pose velocity
    duk_pop_3(ctx);
    // ...
    return 0;
}

// function setMotorInterpolate(data: {pose: number[], period: number[]});
// TODO

// function setMotorParam(data: {paramType: command.SetParamType, params1: number[], params2: number[]}) // params2 is not used (undefined) in case PT_CURRENT
// TODO

// function resetSensor(data: {resetSensorFlag: command.ResetSensorFlags});
// TODO

////////////////////////////////////////////////////////
//////////////////////// receive functions /////////////
////////////////////////////////////////////////////////
void commandMessageHandler(void* buffer, size_t buffer_size) {
    UdpRetPacket* ret = (UdpRetPacket*) (((short*)buffer) - 1);
    switch (ret.command)
    {
        case CI_BOARD_INFO:
            // function onReceiveCIBoardinfo(data: {systemId: number, nTarget: number, nMotor:number, nCurrent: number, nForces:number, nTouch: number, macAddress: ArrayBuffer});
            //  ret.data[0], ret.data[1], ret.date[2] ... corresponds. TODO: Call js function with them.
            break;
        case CI_SENSOR:
            // TODO
            // function onReceiveCISensor(data: {pose: number[], current: number[], force: number[]});
            //  pose[i] = ret.data[i];
            //  current[i] = ret.data[allBoards.GetNTotalMotor() + i]
            //  force[i] = ret.data[allBoards.GetNTotalMotor() + allBoards.GetNTotalCurrent() + i]
            //  touch [i] = ret.data[allBoards.GetNTotalMotor() + allBoards.GetNTotalCurrent() + allBoards.GetNTotalForce() + i];
            break;
        case CI_DIRECT:
            // function onReceiveCIDirect(data: {pose: number[], velocity: number[]});
            //  pose[i] = ret.data[i]
            //  vel[i] = ret.data[allBoards.GetNTotalMotor() + i]

            // ...
            // get function
            duk_get_global_string(ctx, "softrobot");
            duk_require_object(ctx, -1);
            duk_get_prop_string(ctx, -1, "message_command");
            duk_get_prop_string(ctx, -1, "onReceiveCIDirect");
            // ... softrobot message_command onReceiveCIDirect

            // get parameter
            duk_push_object(ctx);
            // ... softrobot message_command onReceiveCIDirect obj

            // put prop pose
            duk_push_array(ctx);
            for(size_t i=0; i<nMotor; i++){
                duk_push_int(ctx, *(++i16p));
                duk_put_prop_index(ctx, -2, i);
            }
            // ... softrobot message_command onReceiveCIDirect obj pose
            duk_put_prop_string(ctx, -2, "pose");
            // ... softrobot message_command onReceiveCIDirect obj

            // TODO put prop velocity

            //  call callback
            // ... softrobot message_command onReceiveCIDirect obj
            duk_call(ctx, 1);
            // ... softrobot message_command return_value

            duk_pop_3(ctx);
            // ...

            break;
        case CI_INTERPOLATE:
            // function onReceiveCIInterpolate(data: {pose: number[], targetCountReadMin: number, targetCountReadMax: number, tickMin: number, tickMax: number});
            // TODO 
            break;
        case CI_SETPARAM:
            // function onReceiveCISetparam();
            // TODO  
            break;
        case CI_RESET_SENSOR:
            // function onReceiveCIResetsensor();
            // TODO 
            break;
        default:
            break;
    }
}

extern "C" duk_ret_t ModuleSRCommand(duk_context *ctx) {
    ADD_FUNCTION("setMotorDirect", setMotorDirect, 1);      // receive 1 parameter as input

    return 0;
}