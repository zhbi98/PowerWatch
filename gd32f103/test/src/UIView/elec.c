
#include "elec.h"

struct elec_calc_t elec = {
    .mah  = 0.0,
    .mwh  = 0.0,
    .time = 0.0,
    .status = 1,
};

void set_elec_status(unsigned char status)
{
    elec.status = status;
}

unsigned char get_elec_status()
{
    return elec.status;
}

float get_elec_calc_mah()
{
    return elec.mah;
}

float get_elec_calc_mwh()
{
    return elec.mwh;
}

float get_elec_calc_time()
{
    return elec.time;
}

void elec_calc_clear()
{
    elec.mah  = 0.0;
    elec.mwh  = 0.0;
    elec.time = 0.0;
}

void elec_calc_hanlder(float current, float power)
{
    if (elec.status == 0)
        return;
    elec.mah  = elec.mah + (float)(current * ELEC_TIME);
    elec.mwh  = elec.mwh + (float)(power * ELEC_TIME);
    elec.time = elec.time + 0.1;
}
