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

#define INT_TIME 20.0f /*20ms*/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

qflow_t qflow;

/**********************
 * GLOBAL FUNCTIONS
 **********************/

void qflow_update(float cur, float pow)
{
    qflow.current = cur;
    qflow.power = pow;
}

void qflow_int()
{
    float current = qflow.current;
    float power = qflow.power;

    float d_mah = current * INT_TIME;
    float d_mwh = power * INT_TIME;

    d_mah = d_mah / 3600000.0;
    d_mwh = d_mwh / 3600000.0;

    qflow.qflow_mah += d_mah;
    qflow.qflow_mwh += d_mwh;
}
