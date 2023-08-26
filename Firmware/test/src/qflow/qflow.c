/**
 * @file qflow.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "qflow.h"

/*********************
 *      DEFINES
 *********************/

#define QTIME  20U /*20ms*/
#define HOUR_1 3600000U /*3600000ms*/ 

/**********************
 * TYPEDEFS
 **********************/

qflow_t qflow;

/**********************
 * STATIC PROTOTYPES
 **********************/

static void update();

/**********************
 * GLOBAL FUNCTIONS
 **********************/

void qflow_take(float cur, float pow)
{
    qflow.current = cur;
    qflow.power = pow;
}

void update()
{
    float current = qflow.current;
    float power = qflow.power;

    float d_mah = current * QTIME;
    float d_mwh = power * QTIME;

    d_mah = d_mah / HOUR_1;
    d_mwh = d_mwh / HOUR_1;

    qflow.qflow_mah += d_mah;
    qflow.qflow_mwh += d_mwh;
}

void qflow_update()
{
    uint32_t tick = qflow.sys_time;
    tick -= qflow.last_tick;
    if (tick >= QTIME) {
        qflow.last_tick = \
        qflow.sys_time;
        update();
    }
}

void qflow_tick_inc(uint32_t tick_period)
{
    qflow.sys_time += tick_period;
}
