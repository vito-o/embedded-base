#include "cmd_cp.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>


#define DEBUG

int cmd_cp_execute(cmd_t *pcmd)
{
    if (pcmd == NULL)
        return -1;

    int ret;

#ifdef DEBUG
    print_command_struct(pcmd);
#endif

    cp_file_info_t fileinfo;

    // 解析路径并存储到 cp_file_info_t 结构体
    ret = cmd_cp_parse_path(&fileinfo, pcmd);
    if (ret == -1)
        return -1;

    // 解析文件类型
    ret = cmd_cp_parse_type(&fileinfo);
    if (ret == -1)
        return -1;

    // 根据情况来处理不同的cp情况
    ret = cmd_cp_dispatch(&fileinfo);
    if (ret == -1)
        return -1;

    return 0;
}  


int cmd_cp_parse_path(cp_file_info_t *pfileinfo, cmd_t *pcmd)
{
    if (pfileinfo == NULL || pcmd == NULL)
        return -1;

    strcpy(pfileinfo->src_path, pcmd->cmd_arg_list[0]);
    strcpy(pfileinfo->dest_path, pcmd->cmd_arg_list[1]);

#ifdef DEBUG
    printf("[DEBUG] src path < %s >\n", pfileinfo->src_path);
    printf("[DEBUG] dest path < %s >\n", pfileinfo->dest_path);
#endif

    return 0;
}


int cmd_cp_parse_type(cp_file_info_t *pfileinfo) 
{
    enum file_type ftype;

    ftype = get_file_type(pfileinfo->src_path);

    if (ftype == FT_ERROR || ftype == FT_UNKNOWN)
        return -1;
    else 
        pfileinfo->src_ftype = ftype;

#ifdef DEBUG
    if (pfileinfo->src_ftype == FT_FILE)
        printf("File\n");
    else if (pfileinfo->src_ftype == FT_DIR)
        printf("DIR.\n");
#endif

    return 0;
}


enum file_type get_file_type(const char *path)
{
    int ret;

    struct stat statbuf;

    ret = stat(path, &statbuf);
    if (ret == -1)
    {
        perror("stat():");
        return FT_ERROR;
    }

    // 判断是否为目录
    if (S_ISDIR(statbuf.st_mode))
        return FT_DIR;
    else if (S_ISREG(statbuf.st_mode))
        return FT_FILE;

    return FT_UNKNOWN;
}


int cmd_cp_dispatch(cp_file_info_t *pfileinfo) {
    if (pfileinfo->src_ftype == FT_FILE)
    {
        printf("cp file\n");
        return cmd_cp_file(pfileinfo->src_path, pfileinfo->dest_path);
    }
    else if (pfileinfo->src_ftype == FT_DIR) 
    {
        printf("cp dir\n");
        return cmd_cp_directory(pfileinfo->src_path, pfileinfo->dest_path);
    }
}

int cmd_cp_file(const char *src, const char *dest)
{
    if (src == NULL || dest == NULL)
        return -1;

    FILE *fp_src = NULL, *fp_dest = NULL;
    size_t rbytes = 0, wbytes = 0;
    char buffer[SZ_BUFFER] = {0};

#ifdef DEBUG
    printf("[DEBUG] %s ----> %s\n", src, dest);
#endif

    fp_src = fopen(src, "r");
    if (fp_src == NULL)
    {
        perror("[ERROR] src fopen(): ");
        return -1;
    }

    fp_dest = fopen(dest, "w+");
    if (fp_dest == NULL)
    {
        perror("[ERROR] dest fopen(): ");
        return -1;
    }

    for (;;)
    {
        rbytes = fread(buffer, sizeof(char), SZ_BUFFER, fp_src);
        if (rbytes > 0)
        {
            wbytes = fwrite(buffer, sizeof(char), rbytes, fp_dest);
            if (wbytes != rbytes)
            {
                perror("[ERROR] fwrite(): ");
                return -1;
            }
        }
        else
            break;
    }

    fclose(fp_src);
    fclose(fp_dest);
}

int cmd_cp_directory(const char *src, const char *dest)
{
    int ret;
    DIR *pdir = NULL;
    struct dirent *pdrient = NULL; 

    cp_file_info_t info;

    // 创建目标目录
    ret = mkdir(dest, 0777);
    if (ret == -1)
    {
        perror("[DEBUG] mkdir(): ");
        return -1;
    }

    pdir = opendir(src);
    if (pdir == NULL)
    {
        perror("[error] opendir(): ");
        return -1;
    }

    for(;;)
    {
        pdrient = readdir(pdir);
        if (pdrient == NULL)
            break;

        if (
            strcmp(pdrient->d_name, ".") == 0 ||
            strcmp(pdrient->d_name, "..") == 0 )
        {
            continue;
        }

#ifdef DEBUG
    printf("[DEBUG]: filename < %s >\n", pdrient->d_name);
#endif

        // 合成路径
        make_path(&info, src, dest, pdrient->d_name);

#ifdef DEBUG
    printf("[DEBUG]: src path < %s >\n", info.src_path);
    printf("[DEBUG]: dest path < %s >\n", info.dest_path);
#endif

        // 获取源目录文件类型
        info.src_ftype = get_file_type(info.src_path);

        // 判断是目录则递归复制
        if (info.src_ftype == FT_DIR) 
            cmd_cp_directory(info.src_path, info.dest_path);
        // 判断是文件则直接复制
        else if (info.src_ftype == FT_FILE)
            cmd_cp_file(info.src_path, info.dest_path);
    }

    closedir(pdir);

    return 0;
}


void make_path(cp_file_info_t *pfileinfo, 
               const char *spath,
               const char *dpath,
               const char *filename)
{
    memset(pfileinfo->src_path, 0, sizeof(pfileinfo->src_path));
    memset(pfileinfo->dest_path, 0, sizeof(pfileinfo->dest_path));

    strcpy(pfileinfo->src_path, spath);
    strcat(pfileinfo->src_path, "/");
    strcat(pfileinfo->src_path, filename);

    strcpy(pfileinfo->dest_path, dpath);
    strcat(pfileinfo->dest_path, "/");
    strcat(pfileinfo->dest_path, filename); 
}