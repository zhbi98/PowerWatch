/**
 * @file kalman.h
 *
 */

#ifndef __KALMAN_H__
#define __KALMAN_H__

/*********************
 *      INCLUDES
 *********************/

#include <stdbool.h>
#include <stdint.h>
#include "gd32f10x.h"
#include "ina226.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**
 * Describe the historical parameters
 * of the Kalman filter.
 */
typedef struct {
    float cur_est;
    float last_est;
    float K_gain;
    float Y;
} km_filte_t;

/**
 * Filtered voltage, current and power data.
 */
typedef struct {
    float filte_volt;
    float filte_cur;
    float filte_pow;
} ina226_filted_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void ina226_filte_work();
float ina226_filte_get_volt();
float ina226_filte_get_cur();
float ina226_filte_get_pow();

#endif /*__KALMAN_H__*/
