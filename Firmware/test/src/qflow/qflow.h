/**
 * @file qflow.h
 *
 */

#ifndef __PUTCAPACITY_H__
#define __PUTCAPACITY_H__

/*********************
 *      INCLUDES
 *********************/

#include <stdint.h>

/**********************
 *      TYPEDEFS
 **********************/

/*Construct a qflow type*/
typedef struct {
    float qflow_mah;
    float qflow_mwh;
    float current;
    float power;
    uint32_t tick;
} qflow_t;

extern qflow_t qflow;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void qflow_update(float cur, float pow);
void qflow_int();

#endif /*__PUTCAPACITY_H__*/
