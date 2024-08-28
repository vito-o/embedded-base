#include "cmd_ls.h"

// ls -l <path>
int cmd_ls_execute(cmd_t *pcmd)
{
    if (pcmd == NULL)
        return -1;

#ifdef DEBUG
    print_command_struct(pcmd);
#endif

    int ret;

    if (pcmd->cmd_arg_count != 2)
    {
        fprintf(stderr, "COmmand argument Error.\n");
        return -1;
    }

    if (pcmd->cmd_arg_list[1] != NULL)
        return cmd_list_directory(pcmd->cmd_arg_list[1]);
    else 
        return -1;

    return 0;
}

int cmd_list_directory(const char *dirpath)
{
    DIR *pdir = NULL;
    struct dirent *pdirent = NULL;
    char path[128] = {0};

    file_attr_t attr;

    pdir = opendir(dirpath);
    if (pdir == NULL)
    {
        perror("open(): ");
        return -1;
    }

    while((pdirent = readdir(pdir)) != NULL)
    {
        if (strcmp(pdirent->d_name, ".") == 0 || 
            strcmp(pdirent->d_name, "..") == 0)
        {
            continue;    
        }

#ifdef DEBUG
    printf("[DEBUG] filename < %s >\n", pdirent->d_name);
#endif

        memset(&attr, 0, sizeof(attr));

        // 合成目录下的文件路径
        make_path_ls(path, dirpath, pdirent->d_name);

        if (pdirent->d_type == DT_LNK)
            get_file_attr(&attr, path, pdirent->d_name, true);
        else
            get_file_attr(&attr, path, pdirent->d_name, false);

#ifdef DEBUG
    show_file_attributes(&attr);
#endif

    }

    closedir(pdir);

    return 0;
}

// ls -l test   test/1.txt 
void make_path_ls(char *path,const char *dirpath,const char *filename) 
{
    strcpy(path, dirpath);
    strcat(path, "/");
    strcat(path, filename);
}

/**
 * pattr: 自定义文件属性结构体指针
 * path: 目录路径
 * filename: 文件名
 * islink : 是否为软链接
 */
int get_file_attr(struct file_attribute *pattr, const char *path,
                                const char *filename, bool islink)
{
    int ret;
    // stat: 获取的是符号链接指向的目标文件的属性信息。
    // lstat: 获取的是符号链接本身的属性信息。
    if (islink)
        ret = lstat(path, &pattr->f_attr_stat_info);
    else
        ret = stat(path, &pattr->f_attr_stat_info);

    if (ret == -1)
    {
        perror("[ERROR] stat() : ");
		return -1;
    }

    get_file_type_ls(pattr);

    get_file_type_permission(pattr);

    return 0;
}

int get_file_type_ls(struct file_attribute *pattr)
{
    mode_t mode = pattr->f_attr_stat_info.st_mode;

    switch(mode & S_IFMT)   // 计算具体文件类型的 bit
    {
        case S_IFBLK :
            pattr->f_attr_type = 'b';
            break;

        case S_IFCHR :
            pattr->f_attr_type = 'c';
            break;

        case S_IFDIR :
            pattr->f_attr_type = 'd';
            break;

        case S_IFIFO :
            pattr->f_attr_type = 'p';
            break;

        case S_IFLNK :
            pattr->f_attr_type = 'l';
            break;

        case S_IFREG :
            pattr->f_attr_type = '-';
            break;

        case S_IFSOCK:
            pattr->f_attr_type = 's';
            break;

        default:
            break;
    }
}

void show_file_attributes(struct file_attribute *pattr)
{
    printf(" %c", pattr->f_attr_type);  // 文件类型
    printf(" %s", pattr->f_attr_permission);  // 权限
    printf(" %ld", pattr->f_attr_stat_info.st_nlink);  // 硬链接

    putchar('\n');
}

void get_file_type_permission(struct file_attribute *pattr)
{
    mode_t mode = pattr->f_attr_stat_info.st_mode;

    int i, index = 0;
    char perm[] = { 'r', 'w', 'x' };

    for (i = 8; i >= 0; i--) 
    {
        if ((mode >> i) & 0x01)
            pattr->f_attr_permission[index] = perm[index % 3];
        else
            pattr->f_attr_permission[index] = '-';

        index++;
    }
}