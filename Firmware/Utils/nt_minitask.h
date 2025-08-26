/**
 * @file nt_minitask.h
 *
 */

#ifndef __NT_MINITASK_H__
#define __NT_MINITASK_H__

/*********************
 *      INCLUDES
 *********************/

#include <stdio.h>
#include <stdint.h>

/*********************
 *      DEFINES
 *********************/

#define TASK_CNT 5

/**********************
 *      TYPEDEFS
 **********************/

typedef uint32_t (* nt_task_cb_t)();

/**
 * User-defined type to store required data for each task
 */
typedef struct {
    nt_task_cb_t task_cb; /**< Pointer to the task*/
    uint32_t delay;                /**< delay (ticks) until the task will (next) be run*/
    uint32_t period;               /**< Interval (ticks) between subsequent runs*/
} nt_task_t;

/**
 * Construct a task manager type
 */
typedef struct {
    nt_task_t nt_task_list[TASK_CNT];
    uint32_t cur_task_id;
    uint32_t tick_count;
} nt_task_manager_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void nt_task_add(nt_task_cb_t tcb, const uint32_t _delay, 
    const uint32_t _period);
void nt_task_remove(nt_task_cb_t tcb);
void nt_task_path(nt_task_cb_t tcb, const uint32_t _delay, 
    const uint32_t _period);
void nt_task_handler();
uint32_t nt_task_get_cur_id();
void nt_task_tick_inc(uint32_t tick_period);

#endif /*__NT_MINITASK_H__*/
