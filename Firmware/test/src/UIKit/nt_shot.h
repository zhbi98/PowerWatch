/**
 * @file nt_shot.h
 *
 */

#ifndef __NT_SHOT_H__
#define __NT_SHOT_H__

/*********************
 *      INCLUDES
 *********************/

#include "lvgl.h"
#include "log.h"

/*********************
 *      DEFINES
 *********************/

#define PIC_USE_SERIAL    1U /**< Image data is sent by serial port*/
#define PIC_USE_USB       0U /**< Image data is sent by usb port*/
#define PIC_USE_FS        0U /**< Image data write to file system*/

/****************************************
 *   DATA-DRIVEN INTERFACE DEFINES
 ****************************************/

/*Define your preferred data-driven interface here*/

#if (PIC_USE_SERIAL != 0)
#define PIC_WRITE_BYTE(byte) \
    do { \
    } while(0)
#endif

#if (PIC_USE_USB != 0)
#define PIC_WRITE_BYTE(byte) \
    do { \
    } while(0)
#endif

#if (PIC_USE_FS != 0)
#define PIC_WRITE_BYTE(byte) \
    do { \
    } while(0)
#endif

#define SCAN_LINE         60U /**< Maximum number of display buffer rows*/
#define ENCODE_JPEG       0U  /**< Whether compression in JPG format is required*/

/**********************
 *      TYPEDEFS
 **********************/

/*Construct a picture shot type*/
typedef struct {
    uint8_t shot_begin;
    uint8_t picdesc;
    uint8_t shot_cnt;
    uint8_t cnt_max;
} nt_picshot_t;

/*Whether the screenshot task is started*/
extern nt_picshot_t picshot;
#define PIC_SHOT_BEGIN() \
        (picshot.shot_begin)

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Start the snapshot, initialization masks, freeze the graphics refresh, 
 * and synchronize the display area.
 */
void picshot_execute();
/**
 * Flushes the image content to the specified data stream.
 * @param color_p pointer to display buffer.
 * @param count number of pixels in the current display buffer.
 */
void picshot_flush(lv_color_t * color_p, uint32_t count);

#endif /*__NT_SHOT_H__*/
