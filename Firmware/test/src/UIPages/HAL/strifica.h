/**
 * @file vstrifica.h
 *
 */

#ifndef __CURATION_H__
#define __CURATION_H__

/*********************
 *      INCLUDES
 *********************/

#include <stdint.h>
#include <math.h>

/*********************
 *      DEFINES
 *********************/

#define VSLEN 10U
#define USLEN 4U

/**********************
 *      TYPEDEFS
 **********************/

/**
 * NT vstrifica unit type codes.
 */
enum {
    NT_UNIT_VOLT = 0,
    NT_UNIT_CUR,
    NT_UNIT_POW,
    NT_UNIT_MAH,
    NT_UNIT_MWH,
};

typedef uint8_t nt_unit_type_t;

/*Construct a vstrifica type*/
typedef struct {
    uint8_t value[VSLEN];
    uint8_t unit[USLEN];
    uint8_t full[VSLEN + USLEN];
    uint8_t uid;
} nt_strifica_t;

extern nt_strifica_t vstrifica;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void strifica(float oridata, uint8_t _type);

#endif /*__CURATION_H__*/
