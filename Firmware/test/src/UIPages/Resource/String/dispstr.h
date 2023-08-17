/**
 * @file dispstr.h
 *
 */

#ifndef __DISPSTR_H__
#define __DISPSTR_H__

/*********************
 *      INCLUDES
 *********************/

#include <stdint.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**
 * NT display string idx.
 */
enum {
    NT_V = 0,
    NT_MV,
    NT_UA,
    NT_MA,
    NT_A,
    NT_RESTART,
    NT_HZ,
    NT_FREQ,
    NT_CELS,
    NT_FAHR,
    NT_DUTY,
    NT_X1X3,
    NT_MODE,
    NT_UP,
    NT_DOWN,
    NT_STR,
};
typedef uint8_t nt_dispstr_t;

extern const uint8_t * const dispstr[];

/**
 * Get NT display string by idx.
 */
#define NT_DISP_STR(x) (dispstr[x])

#endif /*__DISPSTR_H__*/
