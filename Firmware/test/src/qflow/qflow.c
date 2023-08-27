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

#define QFLOW_PROID 20U /*20ms*/
#define HOUR_1 3600000U /*3600000ms*/ 
#define QFLOW_REPEAT 1U /*ms*/

/**********************
 * TYPEDEFS
 **********************/

qflow_t qflow;

const uint32_t TICK = MS_TO_TICKS(QFLOW_PROID, QFLOW_REPEAT);

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

    float d_mah = current * QFLOW_PROID;
    float d_mwh = power * QFLOW_PROID;

    d_mah = d_mah / HOUR_1;
    d_mwh = d_mwh / HOUR_1;

    qflow.qflow_mah += d_mah;
    qflow.qflow_mwh += d_mwh;
}

void qflow_work()
{
    uint32_t tick = qflow.sys_time;
    tick -= qflow.last_tick;
    if (tick >= TICK) {
        qflow.last_tick = \
        qflow.sys_time;
        update();
    }
}

void qflow_tick_inc(uint32_t tick_period)
{
    qflow.sys_time += tick_period;
}
