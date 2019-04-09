#include <stdio.h>
#include <duktape.h>

#include "duktape_event.h"
#include "duktape_utils.h"
#include "module_srcommand.h"
#include "UdpCom.h"

// send functions
static duk_ret_t setMotorDirect(duk_context* ctx) {
    // ... obj
    duk_require_object(ctx, -1);

    duk_get_prop_string(ctx, -1, "pose");
    // ... obj pose
    if (!duk_is_array(ctx, -1)) {
        duk_pop_2();
        return DUK_ERR_TYPE_ERROR;
    }
    size_t n0 = duk_get_length(ctx, -1);

    duk_get_prop_string(ctx, -2, "velocity");
    // ... obj pose velocity
    if (!duk_is_array(ctx, -1)) {
        duk_pop_3();
        return DUK_ERR_TYPE_ERROR;
    }
    size_t n1 = duk_get_length(ctx, -1);

    size_t len = n0 + n1;
    // TODO create buffer

    // iterate pose
    for(int i=0; i<n0; i++){
        duk_get_prop_index(ctx, -2, i);
        // ... obj pose velocity p

        int16_t p = duk_get_int(ctx, -1);
        // TODO put p into buffer

        duk_pop(ctx);
        // ... obj pose velocity
    }

    // iterate velocity
    for(int i=0; i<n1; i++){
        duk_get_prop_index(ctx, -1, i);
        // ... obj pose velocity v

        int16_t v = duk_get_int(ctx, -1);
        // TODO put v into buffer

        duk_pop(ctx);
        // ... obj pose velocity
    }

    // TODO use UdpCom_OnReceiveServer to send command

    // ... obj pose velocity
    duk_pop_3();
    // ...

    return 0;
}

// receive functions
static duk_ret_t commandMessageHandler(duk_context* ctx) {
    // ... bin info
    duk_size_t buffer_size;
    void* p = duk_get_buffer_data(ctx, -2, &buffer_size);

    duk_get_prop_string(ctx, -1, "nTarget");
    // .. bin info nTarget
    size_t nTarget = duk_get_int(ctx, -1);
    duk_pop();
    // .. bin info

    // TODO get other elements in info
    size_t nMotor;

    int16_t* i16p = (int16_t*)p
    switch (i16p[0])
    {
        case CI_DIRECT:
            // get function
            duk_get_global_string(ctx, "softrobot");
            duk_require_object(ctx, -1);
            duk_get_prop_string(ctx, -1, "message_command");
            duk_get_prop_string(ctx, -1, "onReceiveCIDirect");

            // get parameter
            duk_push_object(ctx);

            duk_push_array(ctx);
            for(size_t i=0; i<nMotor; i++){
                duk_push_int(ctx, *(++i16p));
                duk_put_prop_index(ctx, -1, i);
            }
            duk_put_prop_string(ctx, -1, "pose");

            // TODO put prop velocity

            //  call callback
            duk_call(ctx, 1);

            duk_pop_2();

            break;
    
        default:
            break;
    }
}

duk_ret_t ModuleSRCommand(duk_context *ctx) {
    ADD_FUNCTION("setMotorDirect", setMotorDirect, 1);      // receive 1 parameter as input

    ADD_FUNCTION("commandMessageHandler", commandMessageHandler, 2);      // receive 2 parameters as input

    return 0;
}