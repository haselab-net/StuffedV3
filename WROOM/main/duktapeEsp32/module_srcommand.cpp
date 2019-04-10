#include <iostream>
#include <map>
extern "C" {

#include <duktape.h>
#include "duktape_event.h"
#include "duktape_utils.h"
#include "duktape_jsfile.h"
}
#include "module_srcommand.h"
#include "../softRobot/UdpCom.h"
#include "../softRobot/AllBoards.h"

static const char* Tag = "SRCmd";

static std::map<std::string, uint32_t> stash_key_map;

////////////////////////////////////////////////////////
//////////////////////// send functions ////////////////
////////////////////////////////////////////////////////

// function requireBoardInfo();
static duk_ret_t requireBoardInfo(duk_context* ctx) {
    return 0;
}

// function requireSensorInfo();
static duk_ret_t requireSensorInfo(duk_context* ctx) {
    return 0;
}

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
	UdpCmdPacket* cmd = udpCom.PrepareCommand(CI_DIRECT, 1);
    if (!cmd) return DUK_ERR_ERROR;
    if (cmd->length != (2+n0+n1)*2) return DUK_ERR_TYPE_ERROR;

    // set motor positions
    for(int i=0; i<n0; i++){
        duk_get_prop_index(ctx, -2, i);
        cmd->SetMotorPos(duk_get_int(ctx, -1), i);
        duk_pop(ctx);
    }
    // set motor velocities
    for(int i=0; i<n1; i++){
        duk_get_prop_index(ctx, -1, i);
        cmd->SetMotorVel(duk_get_int(ctx, -1), i);
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
static duk_ret_t setMotorInterpolate(duk_context* ctx) {
    // ... obj
    duk_require_object(ctx, -1);

    duk_get_prop_string(ctx, -1, "pose");
    // ... obj pose
    if (!duk_is_array(ctx, -1)) {
        duk_pop_2(ctx);
        return DUK_ERR_TYPE_ERROR;
    }
    size_t n0 = duk_get_length(ctx, -1);

    //  Prepare command
	UdpCmdPacket* cmd = udpCom.PrepareCommand(CI_INTERPOLATE, 1);
    if (!cmd) return DUK_ERR_ERROR;
    if (cmd->length != (2+n0+2)*2) return DUK_ERR_TYPE_ERROR;

    // set motor positions
    for(int i=0; i<n0; i++){
        duk_get_prop_index(ctx, -2, i);
        cmd->SetMotorPos(duk_get_int(ctx, -1), i);
        duk_pop(ctx);
    }
    //  set period
    duk_get_prop_string(ctx, -2, "period");
    cmd->SetPeriod(duk_get_int(ctx, -1));

    duk_get_prop_string(ctx, -2, "targetCountWrite");
    cmd->SetPeriod(duk_get_int(ctx, -1));

    //  send the packet
	udpCom.WriteCommand();

    // ... obj pose velocity
    duk_pop_3(ctx);
    // ...
    return 0;
}

// function setMotorParam(data: {paramType: command.SetParamType, params1: number[], params2: number[]}) // params2 is not used (undefined) in case PT_CURRENT
static duk_ret_t setMotorParam(duk_context* ctx) {
    return 0;
}

// function resetSensor(data: {resetSensorFlag: command.ResetSensorFlags});
static duk_ret_t resetSensor(duk_context* ctx) {
    return 0;
}

////////////////////////////////////////////////////////
//////////////////////// register callbacks ////////////
////////////////////////////////////////////////////////
// function registerCallback(name: string, func: function);
static duk_ret_t registerCallback(duk_context* ctx) {
    // ... name func
    const char* name = duk_get_string(ctx, -2);
    std::string name_str(name);

    if(stash_key_map.find(name_str)!=stash_key_map.end()) esp32_duktape_stash_delete(ctx, stash_key_map[name_str]);             // delete last registered callback

    if(!duk_is_function(ctx, -1)) {
        printf("register_packet_callback: not a function\n");
        duk_pop_2(ctx);
        return 0;
    }

    uint32_t stash_key_callback = esp32_duktape_stash_array(ctx, 1);

    if(stash_key_callback==0) printf("register_packet_callback: register callback failed.\n");
    else {
        stash_key_map[name_str] = stash_key_callback;
        printf("register_packet_callback: register callback success with stash key - %d\n", stash_key_callback);
    }

    duk_pop(ctx);

    return 0;
}

////////////////////////////////////////////////////////
//////////////////////// call callbacks ////////////////
////////////////////////////////////////////////////////
// function onReceiveCIBoardinfo(data: {systemId: number, nTarget: number, nMotor:number, nCurrent: number, nForces:number, nTouch: number, macAddress: ArrayBuffer});
static int dataProvider_onReceiveCIBoardinfo(duk_context* ctx, void* context) {
    UdpRetPacket* ret = (UdpRetPacket*)context;

    // get parameter
    duk_push_object(ctx);
    // ... obj

    // put prop pose
    duk_push_array(ctx);
    for(size_t i=0; i<allBoards.GetNTotalMotor(); i++){
        duk_push_int(ctx, ret->GetMotorPos(i));
        duk_put_prop_index(ctx, -2, i);
    }
    // ... obj pose
    duk_put_prop_string(ctx, -2, "pose");

    // put prop velocity
    duk_push_array(ctx);
    for(size_t i=0; i<allBoards.GetNTotalMotor(); i++){
        duk_push_int(ctx, ret->GetMotorVel(i));
        duk_put_prop_index(ctx, -2, i);
    }
    duk_put_prop_string(ctx, -2, "velocity");

    return 1;
}
// function onReceiveCISensor(data: {pose: number[], current: number[], force: number[]});
// function onReceiveCIDirect(data: {pose: number[], velocity: number[]});
// function onReceiveCIInterpolate(data: {pose: number[], targetCountReadMin: number, targetCountReadMax: number, tickMin: number, tickMax: number});
// function onReceiveCISetparam();
// function onReceiveCIResetsensor();

////////////////////////////////////////////////////////
//////////////////////// receive functions /////////////
////////////////////////////////////////////////////////
void commandMessageHandler(UdpRetPacket& ret) {
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
        case CI_DIRECT: {
            event_newCallbackRequestedEvent(
                ESP32_DUKTAPE_CALLBACK_STATIC_TYPE_FUNCTION,
                stash_key_map["onReceiveCIDirect"], // Stash key for stashed callback array
                dataProvider_onReceiveCIBoardinfo, // Data provider parameter
                (void*)&ret // Context parameter
            );
            
            break;
        }
        case CI_INTERPOLATE:
            // // function onReceiveCIInterpolate(data: {pose: number[], targetCountReadMin: number, targetCountReadMax: number, tickMin: number, tickMax: number});
            // // get function
            // duk_get_global_string(ctx, "callbacks");
            // duk_require_object(ctx, -1);
            // duk_get_prop_string(ctx, -1, "onReceiveCIInterpolate");
            // // ... callbacks onReceiveCIInterpolate

            // // get parameter
            // duk_push_object(ctx);
            // // ... callbacks onReceiveCIInterpolate obj

            // // put prop pose
            // duk_push_array(ctx);
            // for(size_t i=0; i<allBoards.GetNTotalMotor(); i++){
            //     duk_push_int(ctx, ret.GetMotorPos(i));
            //     duk_put_prop_index(ctx, -2, i);
            // }
            // // ... callbacks onReceiveCIDirect obj pose
            // duk_put_prop_string(ctx, -2, "pose");
            // // ... callbacks onReceiveCIDirect obj

            // duk_push_int(ctx, ret.GetTargetCountReadMin());
            // duk_put_prop_string(ctx, -1, "targetCountReadMin");

            // duk_push_int(ctx, ret.GetTargetCountReadMax());
            // duk_put_prop_string(ctx, -1, "targetCountReadMax");

            // duk_push_int(ctx, ret.GetTickMin());
            // duk_put_prop_string(ctx, -1, "tickMin");

            // duk_push_int(ctx, ret.GetTickMax());
            // duk_put_prop_string(ctx, -1, "tickMax");

            // //  call callback
            // // ... callbacks onReceiveCIDirect ????? TODO: I' not sure number or args on stack.
            // duk_call(ctx, 1);
            // // ... callbacks return_value

            // duk_pop_3(ctx);
            // // ...
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

////////////////////////////////////////////////////////
//////////////////////// register functions ////////////
////////////////////////////////////////////////////////
extern "C" duk_ret_t ModuleSRCommand(duk_context *ctx) {
    ADD_FUNCTION("requireBoardInfo", requireBoardInfo, 0);      // receive 1 parameter as input
    ADD_FUNCTION("requireSensorInfo", requireSensorInfo, 0);
    ADD_FUNCTION("setMotorDirect", setMotorDirect, 1);
    ADD_FUNCTION("setMotorInterpolate", setMotorInterpolate, 1);
    ADD_FUNCTION("setMotorParam", setMotorParam, 1);
    ADD_FUNCTION("resetSensor", resetSensor, 1);

    ADD_FUNCTION("registerCallback", registerCallback, 2);

    return 0;
}