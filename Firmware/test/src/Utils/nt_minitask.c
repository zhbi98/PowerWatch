/**
 * @file nt_minitask.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "nt_minitask.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

nt_task_manager_t tm = {
    .nt_task_list = {0},
    .cur_task_id = 0,
    .tick_count = 0,
};

/**********************
 * GLOBAL FUNCTIONS
 **********************/

/**
 * Add a task callback function to the task list.
 * @param nt_task_cb pointer to a task callback function.
 * @param _delay The interval between callback functions being executed.
 * @param _period The interval between callback functions being executed.
 */
void nt_task_add(nt_task_cb_t tcb, const uint32_t _delay, 
    const uint32_t _period)
{
    uint32_t task_id = 0;
    nt_task_t * list_p = tm.nt_task_list;

    while (
        (list_p[task_id].task_cb != NULL) && 
        (task_id < TASK_CNT)) task_id++;

    if ((task_id > TASK_CNT) || (!_period)) return;

    list_p[task_id].task_cb = tcb;
    list_p[task_id].delay = _delay + 1;
    list_p[task_id].period = _period;
}

/**
 * Remove the task callback function from the task list.
 * @param nt_task_cb pointer to a task callback function.
 */
void nt_task_remove(nt_task_cb_t tcb)
{
    nt_task_t * list_p = tm.nt_task_list;

    for (uint32_t i = 0; i < TASK_CNT; ) {
        if (list_p[i].task_cb != tcb) i++;
        else {
            __disable_irq();
            list_p[i].task_cb = NULL;
            __enable_irq();
            i = TASK_CNT + 1;
        }
   }
}

/**
 * Manually switch the execution of the task callback function.
 * @param nt_task_cb pointer to a task callback function.
 * @param _delay The interval between callback functions being executed.
 * @param _period The interval between callback functions being executed.
 */
void nt_task_path(nt_task_cb_t tcb, const uint32_t _delay, 
    const uint32_t _period)
{
    nt_task_t * list_p = tm.nt_task_list;
    uint32_t cur_id = tm.cur_task_id;

    if ((cur_id > TASK_CNT) || (!_period)) return;

    __disable_irq();
   list_p[cur_id].task_cb = tcb;
   list_p[cur_id].delay = _delay + 1;
   list_p[cur_id].period = _period;
    __enable_irq();
}

/**
 * Iterates through the task list and executes the 
 * task callback function at the end of the cycle time.
 */
void nt_task_handler()
{
   uint32_t stat = 0;
    nt_task_t * list_p = tm.nt_task_list;
    uint32_t cur_id = tm.cur_task_id;

    for (uint32_t i = 0; i < TASK_CNT; i++) {
        if (!list_p[i].delay) {
            tm.cur_task_id = i;
            if (list_p[i].task_cb != NULL)
                stat = (*list_p[i].task_cb)();
            list_p[i].delay = list_p[i].period;
        }
    }
}

/**
 * Gets the list number of the task callback function that is currently executing.
 */
uint32_t nt_task_get_cur_id()
{
    return tm.cur_task_id;
}

/**
 * Each task callback function is timed and used to 
 * execute the corresponding callback function at the end of time.
 */
void nt_task_tick_inc(uint32_t tick_period)
{
    nt_task_t * list_p = tm.nt_task_list;

    tm.tick_count += tick_period;
    for (uint32_t i = 0; i < TASK_CNT; i++) {
        if (list_p[i].delay > 0) {
            list_p[i].delay -= tick_period;
        }
    }
}
