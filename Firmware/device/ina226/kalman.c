/**
 * @file kalman.c
 *
 */

#include "kalman.h"

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static float kalman_filte(km_filte_t * km, float Y_meas);
static float average_filte(avg_filte_t * af, float Y_meas);

static km_filte_t km_filte_volt = {.K_gain = 0.3};
static km_filte_t km_filte_cur = {.K_gain = 0.3};
static km_filte_t km_filte_pow = {.K_gain = 0.3};
static km_filted_t km_filted = {0};

static avg_filte_t avg_filte_volt = {.index = 0};
static avg_filte_t avg_filte_cur = {.index = 0};
static avg_filte_t avg_filte_pow = {.index = 0};
static avg_filted_t avg_filted = {0};

static rectified_t rectified = {0};

/**********************
 * GLOBAL FUNCTIONS
 **********************/

float kalman_filte(km_filte_t * km, float Y_meas)
{
    km->Y = Y_meas;
    /*Updates the current estimate*/
    km->cur_est = km->last_est + km->K_gain * 
        (km->Y - km->last_est);
    /*Updates the last estimate*/
    km->last_est = km->cur_est;
    return km->cur_est;
}

float average_filte(avg_filte_t * af, float Y_meas)
{
    float cur_est = 0; /*The filtered voltage value*/
    uint16_t i;

    /*Add the new origin value to the buffer*/
    af->buffer[af->index] = Y_meas;
    af->index = (af->index + 1) % BUFFER_SIZE;

    /*Result the moving average*/
    for (i = 0; i < BUFFER_SIZE; i++) {
        cur_est += af->buffer[(af->index + i) % BUFFER_SIZE];
    }
    cur_est /= BUFFER_SIZE;

    return cur_est;
}

void ina226_filte_work()
{
    INA226_Update();

    km_filted.volt = kalman_filte(
        &km_filte_volt, 
        INA226_Data.Bus_voltage
    );

    km_filted.cur = kalman_filte(
        &km_filte_cur, 
        INA226_Data.Shunt_Current
    );

    km_filted.pow = kalman_filte(
        &km_filte_pow, 
        INA226_Data.Power
    );
}

float ina226_filte_get_volt()
{
    return km_filted.volt;
}

float ina226_filte_get_cur()
{
    return km_filted.cur;
}

float ina226_filte_get_pow()
{
    return km_filted.pow;
}

/*
RawRange = RawHigh – RawLow;
ReferenceRange = ReferenceHigh – ReferenceLow;
CorrectedValue = (((RawValue – RawLow) * ReferenceRange) / RawRange) + ReferenceLow;
*/

void avg_filte_work()
{
    avg_filted.volt = average_filte(
        &avg_filte_volt,
        ina226_filte_get_volt());

    avg_filted.cur = average_filte(
        &avg_filte_cur,
        ina226_filte_get_cur());

    avg_filted.pow = average_filte(
        &avg_filte_pow,
        ina226_filte_get_pow());
}

float avg_filte_get_volt()
{
    return avg_filted.volt;
}

float avg_filte_get_cur()
{
    return avg_filted.cur;
}

float avg_filte_get_pow()
{
    return avg_filted.pow;
}
