#include <iostream>
#include <cstring>
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

    bool ret = duk_get_global_string(ctx, "callbacks"); // we store all callback functions in global.callbacks 
    if (!ret) { // if no such object, create new
        duk_pop(ctx);
        duk_push_object(ctx);
    }
    // ... name func callbacks
    
    const char* name = duk_get_string(ctx, -3);

    printf("register callback %s", name);

    duk_dup(ctx, -2);
    // ... name func callbacks func

    duk_put_prop_string(ctx, -2, name);
    // ... name func callbacks

    duk_put_global_string(ctx, "callbacks");
    // ... name func

    duk_pop_2(ctx);
    // ...

    return 0;
}

////////////////////////////////////////////////////////
//////////////////////// receive functions /////////////
////////////////////////////////////////////////////////
static bool pushFunction(duk_context* ctx, const char* name) {
    bool ret = duk_get_global_string(ctx, "callbacks"); // we store all callback functions in global.callbacks 
    if (!ret) { return false;}
    
    ret = duk_get_prop_string(ctx, -1, name);
    if (!ret) { return false;}

    return true;
}
static void putPropPos(duk_context* ctx, UdpRetPacket& ret) {
    duk_push_array(ctx);
    for(size_t i=0; i<allBoards.GetNTotalMotor(); i++){
        duk_push_int(ctx, ret.GetMotorPos(i));
        duk_put_prop_index(ctx, -2, i);
    }
    duk_put_prop_string(ctx, -2, "pose");
}
static void putPropVel(duk_context* ctx, UdpRetPacket& ret) {
    duk_push_array(ctx);
    for(size_t i=0; i<allBoards.GetNTotalMotor(); i++){
        duk_push_int(ctx, ret.GetMotorVel(i));
        duk_put_prop_index(ctx, -2, i);
    }
    duk_put_prop_string(ctx, -2, "velocity");
}
static void putPropCur(duk_context* ctx, UdpRetPacket& ret) {
    duk_push_array(ctx);
    for(size_t i=0; i<allBoards.GetNTotalCurrent(); i++){
        duk_push_int(ctx, ret.GetCurrent(i));
        duk_put_prop_index(ctx, -2, i);
    }
    duk_put_prop_string(ctx, -2, "current");
} 
static void putPropFor(duk_context* ctx, UdpRetPacket& ret) {
    duk_push_array(ctx);
    for(size_t i=0; i<allBoards.GetNTotalForce(); i++){
        duk_push_int(ctx, ret.GetForce(i));
        duk_put_prop_index(ctx, -2, i);
    }
    duk_put_prop_string(ctx, -2, "force");
} 
// function onReceiveCIBoardinfo(data: {systemId: number, nTarget: number, nMotor:number, nCurrent: number, nForces:number, nTouch: number, macAddress: ArrayBuffer});
static size_t pushDataCIBoardinfo(duk_context* ctx, UdpRetPacket& ret) {
    duk_push_object(ctx);

    duk_push_number(ctx, ret.data[0]);
    duk_put_prop_string(ctx, -1, "systemId");

    duk_push_number(ctx, ret.data[1]);
    duk_put_prop_string(ctx, -1, "nTarget");

    duk_push_number(ctx, ret.data[2]);
    duk_put_prop_string(ctx, -1, "nMotor");

    duk_push_number(ctx, ret.data[3]);
    duk_put_prop_string(ctx, -1, "nCurrent");

    duk_push_number(ctx, ret.data[4]);
    duk_put_prop_string(ctx, -1, "nForces");

    duk_push_number(ctx, ret.data[5]);
    duk_put_prop_string(ctx, -1, "nTouch");

    void* p = duk_push_fixed_buffer(ctx, 6);
    std::memcpy(p, (void *)&ret.data[6], 6);
    duk_push_buffer_object(ctx, -1, 0, 6, DUK_BUFOBJ_ARRAYBUFFER);
    duk_put_prop_string(ctx, -1, "macAddress");
    duk_pop(ctx);

    return 1;
}
// function onReceiveCISensor(data: {pose: number[], current: number[], force: number[]});
static size_t pushDataCISensor(duk_context* ctx, UdpRetPacket& ret) {
    // get parameter
    duk_push_object(ctx);
    // ... obj

    putPropPos(ctx, ret);
    putPropCur(ctx, ret);
    putPropFor(ctx, ret);

    return 1;
}
// function onReceiveCIDirect(data: {pose: number[], velocity: number[]});
static size_t pushDataCIDirect(duk_context* ctx, UdpRetPacket& ret) {
    // get parameter
    duk_push_object(ctx);
    // ... obj

    // put prop pose
    putPropPos(ctx, ret);

    // put prop velocity
    putPropVel(ctx, ret);

    return 1;
}
// function onReceiveCIInterpolate(data: {pose: number[], targetCountReadMin: number, targetCountReadMax: number, tickMin: number, tickMax: number});
static size_t pushDataCIInterpolate(duk_context* ctx, UdpRetPacket& ret) {
    // get parameter
    duk_push_object(ctx);
    // ... obj

    putPropPos(ctx, ret);

    duk_push_int(ctx, ret.GetTargetCountReadMin());
    duk_put_prop_string(ctx, -1, "targetCountReadMin");
    duk_push_int(ctx, ret.GetTargetCountReadMax());
    duk_put_prop_string(ctx, -1, "targetCountReadMax");
    duk_push_int(ctx, ret.GetTickMin());
    duk_put_prop_string(ctx, -1, "tickMin");
    duk_push_int(ctx, ret.GetTickMax());
    duk_put_prop_string(ctx, -1, "tickMax");

    return 1;
}
// function onReceiveCISetparam();
// function onReceiveCIResetsensor();

void commandMessageHandler(UdpRetPacket& ret) {
	lock_heap();
    //  do not return from this function until unlock (call Give).

    duk_context* ctx= esp32_duk_context;
    duk_idx_t top = duk_get_top(ctx);
    switch (ret.command)
    {
        case CI_BOARD_INFO: {
            bool flag = pushFunction(ctx, "onReceiveCIBoardinfo");
            if(!flag) break;
            size_t argN = pushDataCIBoardinfo(ctx, ret);
            duk_pcall(ctx, argN);
            break;
        }
        case CI_SENSOR:{
            bool flag = pushFunction(ctx, "onReceiveCISensor");
            if(!flag) break;
            size_t argN = pushDataCISensor(ctx, ret);
            duk_pcall(ctx, argN);
            break;
        }
        case CI_DIRECT: {
            bool flag = pushFunction(ctx, "onReceiveCIDirect");
            if(!flag) break;
            size_t argN = pushDataCIDirect(ctx, ret);
            duk_pcall(ctx, argN);
            
            break;
        }
        case CI_INTERPOLATE: {
            bool flag = pushFunction(ctx, "onReceiveCIInterpolate");
            if(!flag) break;
            size_t argN = pushDataCIInterpolate(ctx, ret);
            duk_pcall(ctx, argN);
            
            break;
        }
        case CI_SETPARAM: {
            bool flag = pushFunction(ctx, "onReceiveCISetparam");
            duk_pcall(ctx, 0);
            
            break;
        }
        case CI_RESET_SENSOR: {
            bool flag = pushFunction(ctx, "onReceiveCIResetsensor");
            duk_pcall(ctx, 0);
            
            break;
        }
        default:
            break;
    }

    duk_pop_n(ctx, duk_get_top(ctx)-top);

	unlock_heap();
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