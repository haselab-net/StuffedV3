/**
 * API for controlling hardware
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <stdio.h>

#include "module_jslib.h"

 static duk_ret_t block_pause(duk_context* ctx){
     duk_int_t t = duk_get_int(ctx, -1);

     if(t<=0) return 0;

     vTaskDelay(pdMS_TO_TICKS(t));

     return 0;
 }

 duk_ret_t ModuleJSLib(duk_context *ctx){
     ADD_FUNCTION("block_pause",    block_pause,    0);
 }