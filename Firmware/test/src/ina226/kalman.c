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

static km_filte_t km_ina226_volt = {.K_gain = 0.3};
static km_filte_t km_ina226_cur = {.K_gain = 0.3};
static km_filte_t km_ina226_pow = {.K_gain = 0.3};

ina226_filted_t ina226_filted = {0};

/**********************
 * GLOBAL FUNCTIONS
 **********************/

float kalman_filte(km_filte_t * km, float Y_meas)
{
    km->Y = Y_meas;
    km->cur_est = km->last_est + km->K_gain * 
        (km->Y - km->last_est);
    km->last_est = km->cur_est;
    return km->cur_est;
}

void ina226_filte()
{
    getPower();

    ina226_filted.filte_volt = kalman_filte(
        &km_ina226_volt, 
        ina226_data.voltageVal
    );

    ina226_filted.filte_cur = kalman_filte(
        &km_ina226_cur, 
        ina226_data.Shunt_Current
    );

    ina226_filted.filte_pow = kalman_filte(
        &km_ina226_pow, 
        ina226_data.Power
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
