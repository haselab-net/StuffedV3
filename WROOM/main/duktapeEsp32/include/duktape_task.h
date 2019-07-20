/*
 * duktape_task.h
 *
 *  Created on: Nov 18, 2016 Author: kolban
 *  Modified a lot by hasevr
 */

#if !defined(MAIN_DUKTAPE_TASK_H_)
#define MAIN_DUKTAPE_TASK_H_
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include "../../../components/duktape/src/duktape.h"
#include "duktape_event.h"

//  The first context created from duktape heap.
extern duk_context *heap_context;

#define NJSTHREADS  2   //  Number of threads to process duktape events.
typedef struct JSThread_struct{
    duk_context* ctx;
    duk_thread_state state;
    TaskHandle_t task;
    int stackStart;
    int stackPrev;
}JSThread;
extern JSThread jsThreads[NJSTHREADS];

// Initialize duktape and start threads.
void duktape_start();
// Cleanup duktape and stop threads.
void duktape_end();

// print amount of remained native stack. 
void duktape_print_stack_remain(duk_context* ctx, const char* at);

#define DUK_TRACE_STACK_USAGE
#ifdef DUK_TRACE_STACK_USAGE
#define STRINGIFY(n) #n
#define TOSTRING(n) STRINGIFY(n)
#define DUK_STACK_REMAIN(ctx)   duktape_print_stack_remain(ctx, __FILE__ ":" TOSTRING(__LINE__))
#else
#define DUK_STACK_REMAIN(ctx)   do{}while(0)
#endif

//  lock the duktape heap
void lock_heap();
//  unlock the duktape heap
void unlock_heap();

#endif /* MAIN_DUKTAPE_TASK_H_ */
