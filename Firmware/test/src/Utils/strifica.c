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

nt_strifica_t vstrifica = {0};

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void strified(float _data, uint8_t * buffer);
static uint8_t series(float * d);
/**
 * Choose the format string according to the level of the value.
 */
static const uint8_t * const 
fmtstr[FMT_SERIES] = {
    {
        "%5.3f" /*1.000*/
    },

    {
        "%5.2f" /*10.00*/
    },

    {
        "%5.1f"  /*100.0*/
    },

    {
        "%5.0f" /*1000.*/
    }, 
};

/**
 * Choose the appropriate format according to the 
 * level of the value and the type of data.
 */
static const uint8_t * const 
units[UNIT_TYPE][UNIT_SERIES] = {
    {
        "mV",   "V", "kV"
    },

    {
        "mA",   "A", "kA"
    },

    {
        "mW",   "W", "kW"
    },

    {
        "mAh", "Ah", "kAh"
    },

    {
        "mWh", "Wh", "kWh"
    },
};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

static uint8_t series(float * d)
{
    uint8_t ser = 0;
    float data = *d;

    while (fabs(data) >= 1000.0) {
        data = (float)(data / 1000.0);
        ser++;
    }

    *d = data;

    return ser;
}

static void strified(float _data, uint8_t * buffer)
{
    if (
        (fabs(_data) >= 0.0) && 
        (fabs(_data) < 10.0)
    ) {
        snprintf(
            buffer, 
            VSLEN, 
            fmtstr[0], 
            _data
        );
    } else if (
        (fabs(_data) >= 10.0) && 
        (fabs(_data) < 100.0)
    ) {
        snprintf(
            buffer, 
            VSLEN, 
            fmtstr[1], 
            _data
        );
    } else if (
        (fabs(_data) >= 100.0) && 
        (fabs(_data) < 1000.0)
    ) {
        snprintf(
            buffer, 
            VSLEN, 
            fmtstr[2], 
            _data
        );
    } else if (
        (fabs(_data) >= 1000.0) && 
        (fabs(_data) < 10000.0)
    ) {
        snprintf(
            buffer, 
            VSLEN, 
            fmtstr[3], 
            _data
        );
    }
}

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

    vstrifica.uid = series(&_data);

    memset(vstrifica.value, '\0', VSLEN);
    strified(_data, vstrifica.value);

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
