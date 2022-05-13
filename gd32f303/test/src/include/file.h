
#ifndef __FILE_H__
#define __FILE_H__

#include "stdlib.h"
#include "gd32f30x.h"

#include "ff.h"
#include "usart.h"

static FATFS flash_fs;
static FIL fp;

extern void fatfs_init();
extern FRESULT openWrite(const char *path);
extern FRESULT openRead(const char *path);
extern FRESULT write(void *buff, int32_t len, uint32_t *bw);
extern FRESULT read(void *buff, int32_t len);
extern FRESULT close();
extern FRESULT write_file(const char *path,void *buff[2], int32_t len[2], int32_t segment);
extern FRESULT read_file(const char *path, void *buff, int32_t len);
extern void fatfs_format();

#endif
