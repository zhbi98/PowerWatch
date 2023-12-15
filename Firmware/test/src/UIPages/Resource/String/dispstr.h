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
    NT_RESERVE,
    NT_RESERVE,
    NT_RESERVE,
    NT_RESERVE,
    NT_RESERVE,
    NT_RESERVE,
    NT_RESERVE,
    NT_RESERVE,
    NT_RESERVE,
    NT_RESERVE,
    NT_RESERVE,
    NT_RESERVE,
    NT_RESERVE,
    NT_RESERVE,
    NT_RESERVE,
    NT_RESERVE,
};
typedef uint8_t nt_dispstr_t;

extern const uint8_t * const dispstr[];

/**
 * Get NT display string by idx.
 */
#define NT_DISP_STR(x) (dispstr[x])

#endif /*__DISPSTR_H__*/
