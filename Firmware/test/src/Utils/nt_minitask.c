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
void nt_add_task(uint32_t (* nt_task_cb)(), const uint32_t _delay, 
    const uint32_t _period)
{
    uint32_t task_id = 0;

    while (
        (tm.nt_task_list[task_id].nt_task_cb != NULL) &&
        (task_id < TASK_CNT)
    ) {
        task_id++;
    }

    if ((task_id < TASK_CNT) || (_period > 0)) {
        tm.nt_task_list[task_id].nt_task_cb = nt_task_cb;
        tm.nt_task_list[task_id].delay = _delay + 1;
        tm.nt_task_list[task_id].period = _period;
    }
}

/**
 * Remove the task callback function from the task list.
 * @param nt_task_cb pointer to a task callback function.
 */
void nt_delete_task(uint32_t (* nt_task_cb)())
{
    for (uint32_t i = 0; i < TASK_CNT ; ) {
        if (tm.nt_task_list[i].nt_task_cb != nt_task_cb) i++;
        else {
            __disable_irq();
            tm.nt_task_list[i].nt_task_cb = NULL;
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
void nt_plan_task(uint32_t (* nt_task_cb)(), 
    const uint32_t _delay, const uint32_t _period)
{
    __disable_irq();
    if ((tm.cur_task_id < TASK_CNT) || (_period > 0)) {
       tm.nt_task_list[tm.cur_task_id].nt_task_cb = nt_task_cb;
       tm.nt_task_list[tm.cur_task_id].delay = _delay + 1;
       tm.nt_task_list[tm.cur_task_id].period = _period;
    }
    __enable_irq();
}

/**
 * Iterates through the task list and executes the 
 * task callback function at the end of the cycle time.
 */
void nt_task_handler()
{
   uint32_t stat = 0;

    for (uint32_t i = 0; i < TASK_CNT; i++) {
        if (!tm.nt_task_list[i].delay) {
            tm.cur_task_id = i;
            if (tm.nt_task_list[i].nt_task_cb != NULL)
                stat = (*tm.nt_task_list[i].nt_task_cb)();
            tm.nt_task_list[i].delay = tm.nt_task_list[i].period;
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
void nt_task_tick_inc()
{
    for (uint32_t i = 0; i < TASK_CNT; i++) {
        if (tm.nt_task_list[i].delay > 0) {
            tm.nt_task_list[i].delay--;
        }
    }
    tm.tick_count++;
}
