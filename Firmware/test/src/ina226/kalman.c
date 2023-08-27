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

static km_filte_t km_ina226_volt = {.K_gain = 0.3};
static km_filte_t km_ina226_cur = {.K_gain = 0.3};
static km_filte_t km_ina226_pow = {.K_gain = 0.3};
static ina226_filted_t ina226_filted = {0};

static avg_filte_t avg_filte_volt = {0};
static avg_filte_t avg_filte_cur = {0};
static avg_filte_t avg_filte_pow = {0};
static _filted_t _filted;

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

    ina226_filted.filte_volt = kalman_filte(
        &km_ina226_volt, 
        INA226_Data.Bus_voltage
    );

    ina226_filted.filte_cur = kalman_filte(
        &km_ina226_cur, 
        INA226_Data.Shunt_Current
    );

    ina226_filted.filte_pow = kalman_filte(
        &km_ina226_pow, 
        INA226_Data.Power
    );
}

float ina226_filte_get_volt()
{
    return ina226_filted.filte_volt;
}

float ina226_filte_get_cur()
{
    return ina226_filted.filte_cur;
}

float ina226_filte_get_pow()
{
    return ina226_filted.filte_pow;
}

void _filte_work()
{
    _filted.filte_volt = average_filte(
        &avg_filte_volt,
        ina226_filte_get_volt());

    _filted.filte_cur = average_filte(
        &avg_filte_cur,
        ina226_filte_get_cur());

    _filted.filte_pow = average_filte(
        &avg_filte_pow,
        ina226_filte_get_pow());
}

float _filte_get_volt()
{
    return _filted.filte_volt;
}

float _filte_get_cur()
{
    return _filted.filte_cur;
}

float _filte_get_pow()
{
    return _filted.filte_pow;
}
