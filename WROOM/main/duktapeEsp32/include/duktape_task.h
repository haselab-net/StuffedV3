/*
 * duktape_task.h
 *
 *  Created on: Nov 18, 2016
 *      Author: kolban
 */

#if !defined(MAIN_DUKTAPE_TASK_H_)
#define MAIN_DUKTAPE_TASK_H_

void duktape_init_environment();
void duktape_task(void *ignore);
extern duk_context *esp32_duk_context;

#endif /* MAIN_DUKTAPE_TASK_H_ */
