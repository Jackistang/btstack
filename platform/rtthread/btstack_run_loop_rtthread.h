/*
 * btstack_run_loop_rtthread.h
 *
 * Functions relevant for BTstack rtthread port 
 */

#ifndef BTSTACK_RUN_LOOP_RTTHREAD_H
#define BTSTACK_RUN_LOOP_RTTHREAD_H

#include "btstack_config.h"
#include "btstack_run_loop.h"

#if defined __cplusplus
extern "C" {
#endif

/**
 * @brief Provide btstack_run_loop_rtthread instance for use with btstack_run_loop_init
 */
const btstack_run_loop_t * btstack_run_loop_rtthread_get_instance(void);

/*
 * @brief Execute code on BTstack run loop. Can be used to control BTstack from a different thread
 */
void btstack_run_loop_rtthread_execute_code_on_main_thread(void (*fn)(void *arg), void * arg);

/**
 * @brief Triggers processing of data sources from thread context. 
 * Has to be called after enabling a poll data source to wake-pup run loop.
 */
void btstack_run_loop_rtthread_trigger(void);    

/* API_END */

#if defined __cplusplus
}
#endif

#endif // BTSTACK_RUN_LOOP_RTTHREAD_H