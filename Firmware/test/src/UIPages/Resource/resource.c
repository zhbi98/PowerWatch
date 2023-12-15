/**
 * @file resource.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "resource.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

nt_rm_t rm_font = {0};
nt_rm_t rm_sym = {0};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Initialize existing resources for subsequent use.
 */
void _nt_resource_init()
{
#define IMPORT_FONT(name) \
    do { \
        LV_FONT_DECLARE(font_##name) \
        nt_rm_resource_register(\
            &rm_font, #name, \
            (void *)&font_##name);\
    } while(0)

#define IMPORT_SYM(name) \
    do {\
        LV_IMG_DECLARE(symbol_##name)\
        nt_rm_resource_register(\
            &rm_sym, #name, \
            (void *)&symbol_##name);\
    } while (0)

#include "ResList.inc"
#undef IMPORT_FONT
#undef IMPORT_SYM
}

/**
 * Requests the installed fonts from the device database.
 * @param id the name of the installed font.
 * @return an object pointer to an installed font.
 */
lv_font_t * reqfont(const int8_t * id)
{
    void * ptr = nt_rm_get_resource(&rm_font, id);
    return (lv_font_t *)ptr;
}

/**
 * Requests the installed symbols from the device database.
 * @param id the name of the installed symbol.
 * @return an object pointer to an installed symbol.
 */
lv_font_t * reqsym(const int8_t * id)
{
    void * ptr = nt_rm_get_resource(&rm_sym, id);
    return (lv_font_t *)ptr;
}
