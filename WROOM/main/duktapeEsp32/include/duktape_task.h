/*
 * duktape_task.h
 *
 *  Created on: Nov 18, 2016
 *      Author: kolban
 */

#if !defined(MAIN_DUKTAPE_TASK_H_)
#define MAIN_DUKTAPE_TASK_H_
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "../../../components/duktape/src/duktape.h"

//  The first context created from duktape heap.
extern duk_context *heap_context;

#define NJSTHREADS  2
typedef struct JSThread_struct{
    duk_context* ctx;
    duk_thread_state state;
    TaskHandle_t task;
}JSThread;
extern JSThread jsThreads[NJSTHREADS];


void duktape_init_environment();
void duktape_task(void *ignore);

#include "duktape_event.h"
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

bool handle_event();

void lock_heap();
void unlock_heap();

void duktape_start();
void duktape_end();


#endif /* MAIN_DUKTAPE_TASK_H_ */
