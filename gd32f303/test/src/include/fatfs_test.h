
#ifndef __FATFS_TEST__
#define __FATFS_TEST__

#include "usart.h"
#include "w25q16.h"
#include "ff.h"

extern FATFS fatfs_t;
extern FRESULT res;
extern FIL testfp;

extern uint8_t read_buff[];
extern uint8_t write_buff[];

UINT bw;
UINT br;

extern void fatfs_test();

#endif