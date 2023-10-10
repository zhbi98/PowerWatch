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

#define BUFFER_SIZE 20U

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
    float volt;
    float cur;
    float pow;
} km_filted_t;

/**
 * Rectified voltage, current and power data.
 */
typedef struct {
    float volt;   /*calibrated rawAngle data*/
    float cur;    /*calibrated rawAngle data*/
    float pow;    /*calibrated rawAngle data*/
} rectified_t;

/**
 * Describe the historical parameters
 * of the avg filter.
 */
typedef struct {
    float buffer[BUFFER_SIZE]; /*Buffer*/
    uint16_t index; /*The current window index*/
    uint16_t cnt;
} avg_filte_t;

/**
 * Filtered voltage, current and power data.
 */
typedef struct {
    float volt;
    float cur;
    float pow;
} avg_filted_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void ina226_filte_work();
float ina226_filte_get_volt();
float ina226_filte_get_cur();
float ina226_filte_get_pow();

void avg_filte_work();
float avg_filte_get_volt();
float avg_filte_get_cur();
float avg_filte_get_pow();

#endif /*__KALMAN_H__*/
