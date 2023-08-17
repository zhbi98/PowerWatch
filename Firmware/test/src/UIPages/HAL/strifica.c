/**
 * @file vstrifica.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "strifica.h"

/*********************
 *      DEFINES
 *********************/

#define FMT_SERIES  4U
#define UNIT_TYPE   5U
#define UNIT_SERIES 3U

/**********************
 *      TYPEDEFS
 **********************/

nt_strifica_t vstrifica = {
    .value = {0},
    .unit = {0},
    .uid = 0,
};


/**********************
 *  STATIC PROTOTYPES
 **********************/

/**
 * Choose the format string according to the level of the value.
 * Display format for example: 1.000
 * Display format for example: 10.00
 * Display format for example: 100.0
 * Display format for example: 1000.
 */
static const uint8_t * 
const fmtstr[FMT_SERIES] = {
    "%5.3f",
    "%5.2f",
    "%5.1f",
    "%5.0f",
};

/**
 * Choose the appropriate format according to the 
 * level of the value and the type of data.
 * 1kV  = 1000V  = 1000000mV
 * 1kA  = 1000A  = 1000000mA
 * 1kW  = 1000W  = 1000000mW
 * 1kAh = 1000Ah = 1000000mAh
 * 1kWh = 1000Wh = 1000000mmWh
 */
static const uint8_t * 
const units[UNIT_TYPE][UNIT_SERIES] = {
    {"mV",   "V", "kV" },
    {"mA",   "A", "kA" },
    {"mW",   "W", "kW" },
    {"mAh", "Ah", "kAh"},
    {"mWh", "Wh", "kWh"},
};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
/**
 * Enter an unformatted raw numeric value.
 * @param _oridata raw numeric value.
 * @param _type in what form to convert it.
 */
void strifica(float oridata, uint8_t _type)
{
    uint8_t sym = 0;
    float _data = 0.0;

    if (!sym) _data = fabs(oridata);
    else _data = oridata;

    vstrifica.uid = 0;
    while (fabs(_data) >= 1000.0) {
        _data = (float)(_data / 1000.0);
        vstrifica.uid++;
    }

    memset(vstrifica.value, '\0', VSLEN);
    if (
        (fabs(_data) >= 0.0) && 
        (fabs(_data) < 10.0)
    ) {
        snprintf(
            vstrifica.value, 
            VSLEN, 
            fmtstr[0], 
            _data
        );
    } else if (
        (fabs(_data) >= 10.0) && 
        (fabs(_data) < 100.0)
    ) {
        snprintf(
            vstrifica.value, 
            VSLEN, 
            fmtstr[1], 
            _data
        );
    } else if (
        (fabs(_data) >= 100.0) && 
        (fabs(_data) < 1000.0)
    ) {
        snprintf(
            vstrifica.value, 
            VSLEN, 
            fmtstr[2], 
            _data
        );
    } else if (
        (fabs(_data) >= 1000.0) && 
        (fabs(_data) < 10000.0)
    ) {
        snprintf(
            vstrifica.value, 
            VSLEN, 
            fmtstr[3], 
            _data
        );
    }

    memset(vstrifica.unit, '\0', USLEN);
    snprintf(
        vstrifica.unit, 
        USLEN, 
        "%s", 
        units[_type][vstrifica.uid]
    );

    memset(vstrifica.full, '\0', VSLEN + USLEN);
    snprintf(
        vstrifica.full, VSLEN + USLEN, 
        "%s%s", 
        vstrifica.value,
        vstrifica.unit
    );
}
