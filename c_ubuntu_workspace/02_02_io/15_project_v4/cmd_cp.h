#ifndef __CMD_CP_H__
#define __CMD_CP_H__

#include "cmd_handle.h"

#define SZ_PATH 128
#define SZ_BUFFER 1024

enum file_type {
    FT_DIR = 0,     // 是目录
    FT_FILE = 1,    // 是普通文件
    FT_ERROR = 2,   // 出错
    FT_UNKNOWN = 3,  // 文件类型未知
};

typedef struct cp_file_info {
    enum file_type src_ftype;   //源文件类型
    char src_path[SZ_PATH];     //源文件路径名
    char dest_path[SZ_PATH];    //目标文件路径名
} cp_file_info_t;

extern int cmd_cp_execute(cmd_t *pcmd);

int cmd_cp_parse_path(cp_file_info_t *pfileinfo, cmd_t *pcmd);

enum file_type get_file_type(const char *path);

int cmd_cp_parse_type(cp_file_info_t *pfileinfo);

int cmd_cp_dispatch(cp_file_info_t *pfileinfo);
int cmd_cp_file(const char *src, const char *dest);
int cmd_cp_directory(const char *src, const char *dest);

#endif