
#include "file.h"

FATFS flash_fs;
FIL fp;

void fatfs_init()
{
    FRESULT res;

    res = f_mount(&flash_fs, "1:", 1);

    // res = FR_NO_FILESYSTEM;

    if (res == FR_NO_FILESYSTEM) {
        res = f_mkfs("1:", 0, 0);

        if (res == FR_OK) {
            res = f_mount(NULL, "1:", 1);
            res = f_mount(&flash_fs, "1:", 1);

            // printf("%s\n", "file system init success");
        } else {
            // printf("%s\n", "file system init error 01");
            // while (1);
        }
    } else if (res != FR_OK) {
        // printf("%s\n", "file system init error 02");
        // while (1);
    }
}

void fatfs_format()
{
    FRESULT res;
    res = f_mkfs("1:", 0, 0);

    if (res == FR_OK) {
        res = f_mount(NULL, "1:", 1);
        res = f_mount(&flash_fs, "1:", 1);
    } else {
        while (1);
    }
}

FRESULT openWrite(const char *path)
{
    return f_open(&fp, path, FA_CREATE_ALWAYS | FA_WRITE);
}

FRESULT openRead(const char *path)
{
    FRESULT res;

    res = f_open(&fp, path, FA_READ);

    return res;
}


FRESULT write(void *buff, int32_t len, uint32_t* bw)
{
    FRESULT res;

    res = f_write(&fp, buff, len, bw);
    if (res == FR_OK)
        res = f_sync(&fp);

    return res;
}

FRESULT write_file(const char *path, void *buff[2], int32_t len[2], int32_t segment)
{
    int32_t i;
    uint32_t bw;
    FRESULT res;

    res = f_open(&fp, path, FA_CREATE_ALWAYS | FA_WRITE);
    if(res == FR_OK){
        for (i = 0; i < segment; ++i) {
            res = f_write(&fp, buff[i], len[i], &bw);
            if (res == FR_OK && len[i] == bw) {
                res = f_sync(&fp);
            }
        }
        res = f_close(&fp);
    }

    return res;
}

FRESULT read_file(const char *path, void *buff, int32_t len)
{
    uint32_t bw;
    FRESULT res;

    res = f_open(&fp, path, FA_READ);
    if (res == FR_OK) {
        res = f_read(&fp, buff, len, &bw);
        if(res == FR_OK) {
            res = f_close(&fp);
        }
    }

    return res;
}

FRESULT read(void *buff, int32_t len)
{
    FRESULT res;
    uint32_t br;

    res = f_read(&fp, buff, len, &br);

    return res;
}

FRESULT close()
{ 
    return f_close(&fp);
}
