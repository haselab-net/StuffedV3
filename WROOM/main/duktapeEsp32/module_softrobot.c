#include <stdio.h>
#include <duktape.h>

#include "duktape_event.h"
#include "duktape_utils.h"
#include "module_softrobot.h"
#include "module_jsfile.h"

static uint32_t stash_key_callback = 0;    // stash key for callback function: send_packet
static size_t return_packet_buffer_size;   // the size of buffer we want to send

extern void UdpCom_OnReceiveServer(void* payload, int len);

/*
* handle content in the buffer
* recognize command in the buffer from JS and send instructions to hardware (motors,... etc)
* [0] - packet buffer
*/
static duk_ret_t handle_packet(duk_context *ctx){
    void* buffer;           // pointer of buffer

    // get content of the buffer
    duk_size_t out_size;    // size of the recieved buffer
    buffer = duk_get_buffer_data(ctx, -1, &out_size);
    if(!buffer) {
        printf("Something wrong with the buffer received.\n");
        return DUK_RET_ERROR;
    }
    // do something with the buffer recieved (buffer, out_size)
    printf("handle_packet: a buffer received.\n");
    UdpCom_OnReceiveServer(buffer, out_size);

    // free buffer
    duk_pop(ctx);
    return 0;
}

/*
* register a callback with one parameter: buffer
* the callback would be called when hardware want to send a packet
* [0] - callback function
*/
static duk_ret_t register_packet_callback(duk_context *ctx){
    /*duk_dup(ctx, -1);
    duk_put_global_string(ctx, "send_packet");

    printf("register_packet_callback: an callback function received.\n");

    duk_pop(ctx);*/

    if(stash_key_callback!=0) esp32_duktape_stash_delete(ctx, stash_key_callback);             // delete last registered callback
    if(!duk_is_function(ctx, -1)) {
        printf("register_packet_callback: not a function\n");
        duk_pop(ctx);
        return 0;
    }
    
    stash_key_callback = esp32_duktape_stash_array(ctx, 1);
    
    if(stash_key_callback==0) printf("register_packet_callback: register callback failed.\n");
    else printf("register_packet_callback: register callback success with stash key - %d\n", stash_key_callback);

    return 0;
}

/**
 * Provide callback function with 2 parameters: buffer + buffersize
 */
static int return_packet_dataProvider(duk_context *ctx, void *context) {
    void* p = duk_push_buffer(ctx, return_packet_buffer_size, 0);
    memcpy(p, context, return_packet_buffer_size);
    duk_push_buffer_object(ctx, -1, 0, return_packet_buffer_size, DUK_BUFOBJ_ARRAYBUFFER);
    duk_replace(ctx, -2);
    duk_push_uint(ctx, return_packet_buffer_size);

    return 2;
}

/*
* call registered callback
* [0] - context
* [1] - buffer of command packet
* [2] - size of the buffer
*/
void return_packet(void* buffer, size_t buffer_size) {
    if(stash_key_callback==0) return;

    return_packet_buffer_size = buffer_size;

    event_newCallbackRequestedEvent(
      ESP32_DUKTAPE_CALLBACK_STATIC_TYPE_FUNCTION,
      stash_key_callback, // Stash key for stashed callback array
      return_packet_dataProvider, // Data provider parameter
      buffer // Context parameter
   );

   // call jsfile callback
   jsfile_exec_packet_callback();
}

/**
 * Add native methods to the Softrobot object.
 * [0] - Softrobot Object
 */
duk_ret_t ModuleSoftrobot(duk_context *ctx) {
    ADD_FUNCTION("handle_packet",   handle_packet,  1);             // parameter: 1. buffer content
    ADD_FUNCTION("register_callback", register_packet_callback, 1); // parameter: 1. callback function

    return 0;
}