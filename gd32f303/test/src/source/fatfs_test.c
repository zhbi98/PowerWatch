
#include "fatfs_test.h"

FATFS fatfs_t;
FRESULT res;
FIL testfp;

uint8_t read_buff[1024];
uint8_t write_buff[] = "Hello, World!";

UINT bw;
UINT br;

void fatfs_test()
{
    // printf("%x", read_w25q16_id());
    
    // Install file system
    res = f_mount(&fatfs_t,"1:", 1);
    
    // No file system, now execute flash format
    if (res == FR_NO_FILESYSTEM) {
        // printf("FLASH 没有文件系统, 进行格式化\r\n");
        // flash format 
        res = f_mkfs("1:",0,0);
    
        if (res == FR_OK) {
            // printf("FLASH 成功格式化文件系统\r\n");
            // flash format later, cancle file system install 
            res = f_mount(NULL, "1:", 1);
            // reinstall 
            res = f_mount(&fatfs_t, "1:", 1);
        } else {
            // printf("格式化失败\r\n");
            while (1);
        }
    } else if (res != FR_OK) {
        // others problems
        // printf("Flash 挂载文件系统失败(%d)\r\n", res);
        // printf("可能原因:Flash 初始化不成功\r\n");
        while (1);
    } else {                   
        // file system install success
        // printf("文件系统挂载成功, 进行读写测试\r\n");
    }
    
    // ----------------------- write file test -------------------
    // Writable open files
    // printf("\r\n进行文件写入测试\r\n");
    res = f_open(&testfp, "1:/myfile.txt", FA_CREATE_ALWAYS | FA_WRITE);
    if (res == FR_OK) {
        // printf("打开/创建 myfile.txt 文件成功, 向文件写数据\r\n");
        // write file
        res = f_write(&testfp, write_buff, sizeof(write_buff), &bw);
        if (res == FR_OK) {
            // printf("文件写入成功, 写入字节数据:%d\n", bw);
            // printf("向文件写入的数据为:\r\n%s\r\n", write_buff);
        } else {
            // printf("文件写入失败:(%d)\n", res);
        }
        // write file finish, close file
        f_close(&testfp);
    } else {
        // printf("打开文件失败%d\r\n",res);
    }
    
    // ------------------- read file test --------------------------
    // Readable open files
    // printf("进行文件读取测试\r\n");
    res = f_open(&testfp, "1:/myfile.txt", FA_OPEN_EXISTING | FA_READ);
    if (res == FR_OK) {
        // printf("打开文件成功\r\n");
        res = f_read(&testfp, read_buff, sizeof(read_buff), &br);
        if (res==FR_OK) {
            // printf("文件读取成功,读到字节数据:%d\r\n", br);
            // printf("读取得的文件数据为:\r\n%s \r\n", read_buff);
        } else {
            // printf("%s(%d): 文件读取失败n", __MODULE__, __LINE__, res);
        }
    } else {
        // printf("打开文件失败%d\r\n", res);
    }
    // read file finish, close file
    f_close(&testfp);
    
    // Unuse file system
    f_mount(NULL,"1:", 1);
}
