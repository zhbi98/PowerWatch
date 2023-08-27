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
    float filte_volt;
    float filte_cur;
    float filte_pow;
} ina226_filted_t;

/**
 * Describe the historical parameters
 * of the Kalman filter.
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
    float filte_volt;
    float filte_cur;
    float filte_pow;
} _filted_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void ina226_filte_work();
float ina226_filte_get_volt();
float ina226_filte_get_cur();
float ina226_filte_get_pow();

void _filte_work();
float _filte_get_volt();
float _filte_get_cur();
float _filte_get_pow();

#endif /*__KALMAN_H__*/
