/**
 * @file qflow.h
 *
 */

#ifndef __QFLOW_H__
#define __QFLOW_H__

/*********************
 *      INCLUDES
 *********************/

#include <stdint.h>

/*********************
 *      DEFINES
 *********************/

#define MS_TO_TICKS(ms, base) \
    ((uint32_t)((ms) / (base)))

#define QFLOW_GET_MAH() \
    qflow.qflow_mah
#define QFLOW_GET_MWH() \
    qflow.qflow_mwh

#define QFLOW_TAKE(cur, pow) \
    do { \
        qflow.current = cur; \
        qflow.power = pow; \
    } while (0)

#define QFLOW_TICK_INC(period) \
    do { \
        qflow.sys_time += \
            period; \
    } while (0)

/**********************
 *      TYPEDEFS
 **********************/

/*Construct a qflow type*/
typedef struct {
    float qflow_mah;
    float qflow_mwh;
    float current;
    float power;
    uint32_t sys_time;
    uint32_t last_tick;
} qflow_t;

/*Construct a qflow type*/
typedef struct {
    uint16_t hour;
    uint8_t min;
    uint8_t sec;
} qflow_duration_t;

extern qflow_t qflow;
extern qflow_duration_t qf_dura;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void qflow_take(float cur, float pow);
void qflow_work();
void qflow_tick_inc(uint32_t tick_period);
float qflow_get_mah();
float qflow_get_mwh();
void qflow_dura_work();
uint32_t qflow_dura_get_hour();
uint32_t qflow_dura_get_min();
uint32_t qflow_dura_get_sec();

#endif /*__QFLOW_H__*/
