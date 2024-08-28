#ifndef __CMD_LS_H__
#define __CMD_LS_H__

#include "cmd_handle.h"
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#define SZ_LS_NAME 64
#define SZ_LS_PERMISSION 10
#define SZ_LS_TIME 32
#define SZ_LS_LINK_CONTENT 64

#define DEBUG

typedef struct file_attribute
{
    struct stat f_attr_stat_info;   // 保留系统原来的结构

    char f_attr_type;
    char f_attr_uname[SZ_LS_NAME];  // user name
    char f_attr_gname[SZ_LS_NAME];  // group name
    char f_attr_mtime[SZ_LS_TIME];  // 最后一次修改时间
    char f_attr_permission[SZ_LS_PERMISSION];   // 权限
    char f_attr_name[SZ_LS_NAME];
    char f_attr_link_content[SZ_LS_LINK_CONTENT];

} file_attr_t;

extern int cmd_ls_execute(cmd_t *pcmd);

int cmd_list_directory(const char *dirpath);

/* 获取文件类型 */
int get_file_type_ls(struct file_attribute *pattr);

/* 合成具体的文件路径 */
void make_path_ls(char *path,const char *dirpath,const char *filename);

/* 获取文件属性 */
int get_file_attr(struct file_attribute *pattr,const char *path,
                                const char *filename,bool islink);

void show_file_attributes(struct file_attribute *pattr);

/* 获取文件权限 */
void get_file_type_permission(struct file_attribute *pattr);

#endif