
#ifndef __USB_CDC_H__
#define __USB_CDC_H__

#include "gd32f10x.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
// cdc_acm
#include "cdc_acm_core.h"

extern void usb_cdc_init();
extern void usb_fs_send_string(unsigned char * string);
extern void usb_fs_send_fmt_string(unsigned char * format, ...);

#endif
