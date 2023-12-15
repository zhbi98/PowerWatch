/**
 * @file nt_shot.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "nt_shot.h"

/*********************
 *      DEFINES
 *********************/

#define PIC_ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

/*Writes RGB data to a data-driven device*/
#define WRITE_PIXEL(color_p) \
    do { \
        PIC_WRITE_BYTE(((color_p->full) & 0x1F) << 3); \
        PIC_WRITE_BYTE(((color_p->full >> 5) & 0x3F) << 2); \
        PIC_WRITE_BYTE((color_p->full >> 11) << 3); \
    } while(0)

/**********************
 *      TYPEDEFS
 **********************/

/*Construct a picture shot types*/
nt_picshot_t picshot = {
    .shot_begin = false,
    .picdesc = true,
    .shot_cnt = 0,
    .cnt_max = 0,
};

/*Bmp picture desc, picture size is 320x240 pixel, RGB is used 24bit*/
static const uint8_t picture_desc[54] = {
    0x42, 0x4D, 
    0x36, 0x84, 0x03, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x36, 0x00, 0x00, 0x00,
    0x28, 0x00, 0x00, 0x00,
    0x40, 0x01, 0x00, 0x00,
    0x10, 0xFF, 0xFF, 0xFF, 
    0x01, 0x00, 
    0x18, 0x00, 
    0x00, 0x00,
    0x00, 0x00, 0x00, 0x84, 
    0x30, 0x00, 0x88, 0x13, 
    0x00, 0x00, 0x88, 0x13, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00
};

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void picshot_execute_init();
static void picshot_execute_deinit();
static void picshot_disp_sync();
static void picshot_write_desc();
static uint8_t picshot_is_finish();

/**********************
 *  STATIC FUNCTIONS
 **********************/

static void picshot_execute_init()
{
    picshot.shot_begin = true;
    picshot.picdesc = true;
    picshot.shot_cnt = 0;
    picshot.cnt_max = 0;
}

static void picshot_execute_deinit()
{
    picshot.shot_begin = false;
    picshot.picdesc = true;
    picshot.shot_cnt = 0;
    picshot.cnt_max = 0;
}

/**
 * Marks the display area to be truncated, and refresh
 * the contents of the area to the latest.
 */
static void picshot_disp_sync()
{
    uint16_t width = 0, height = 0;
    lv_obj_t * scr = NULL;

    scr = lv_scr_act();
    width = lv_obj_get_width(scr);
    height = lv_obj_get_height(scr);
    picshot.cnt_max = height / SCAN_LINE;
    lv_obj_invalidate(scr);
}

/**
 * Writes a BMP image format descriptor to the specified data stream.
 */
static void picshot_write_desc()
{
    uint16_t size = 0;

    if (!picshot.picdesc) return;
    size = PIC_ARR_SIZE(picture_desc);

    for (uint8_t i = 0; i < size; i++)
        PIC_WRITE_BYTE(picture_desc[i]);
    picshot.picdesc = false;
}

static uint8_t picshot_is_finish()
{
    uint8_t res = false;
    res = (
        picshot.shot_cnt == 
        picshot.cnt_max
    ) ? true : false;
    return res;
}

/**********************
 * GLOBAL FUNCTIONS
 **********************/

/**
 * Start the snapshot, initialization masks, freeze the graphics refresh, 
 * and synchronize the display area.
 */
void picshot_execute()
{
    picshot_execute_init();
    picshot_disp_sync();
}

/**
 * Flushes the image content to the specified data stream.
 * @param color_p pointer to display buffer.
 * @param count number of pixels in the current display buffer.
 */
void picshot_flush(lv_color_t * color_p, 
                uint32_t count)
{
    picshot_write_desc();
    for (uint32_t i = 0; i < count; i++) {
        WRITE_PIXEL(color_p);
        color_p++;
    }
    picshot.shot_cnt++;
    if (!picshot_is_finish()) return;
    picshot_execute_deinit();
}
