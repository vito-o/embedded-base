#include "cmd_cp.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


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

}