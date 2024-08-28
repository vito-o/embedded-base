#include "cmd_handle.h"

#define DEBUG

/* 命令执行的入口 */
int cmd_execute(char *cmd_str)
{
    cmd_t command;
    int ret;

    if (cmd_str == NULL)
        return -1;

#ifdef DEBUG
    printf("[DEBUG]: cmd_str: < %s >\n", cmd_str);
#endif

    // 初始化结构体
    init_command_struct(&command);

#ifdef DEBUG
    // 打印结构体
    print_command_struct(&command);
#endif

    // 解析命令字符串
    ret = cmd_parse(cmd_str, &command);
    if (ret == -1)
        return -1;

#ifdef DEBUG
    // 打印结构体
    print_command_struct(&command);
#endif

    // 命令分发
    ret = cmd_dispatch(&command);
    if (ret == -1)
        return -1;

    return 0;
}

/* 初始化 */
void init_command_struct(cmd_t *pcmd)
{
    int i;
    memset(pcmd->cmd_name, 0, SZ_NAME);

    for(i = 0; i < SZ_COUNT; i++)
    {
        memset(pcmd->cmd_arg_list[i], 0, SZ_ARG);
    }

    pcmd->cmd_arg_count = 0;
}

/* 打印 */
void print_command_struct(cmd_t *pcmd)
{
    int i;
    printf("-------------------------------------------------\n");
    printf("[DEBUG] cmd name : < %s >\n", pcmd->cmd_name);
    printf("[DEBUG] cmd arg count : < %d >\n", pcmd->cmd_arg_count);
    printf("[DEBUG] cmd arg list : ");
    for (i = 0; i < pcmd->cmd_arg_count; i++)
    {
        printf(" %s ", pcmd->cmd_arg_list[i]);
    }
    printf("\n-------------------------------------------------\n");
}

/* 解析字符串 cp 1.txt 2.txt*/
int cmd_parse(char *cmd_str, cmd_t *pcmd) 
{
    if (cmd_str == NULL || pcmd == NULL)
        return -1;

    int index = 0;
    char *p_cmd_name = NULL;
    char *p_cmd_arg = NULL;

    // strtok分割字符从时，第一次调用只分割出第一个，后面的需要再次调用strtok(NULL, " ")并不再传递第一个参数
    p_cmd_name = strtok(cmd_str, " ");

#ifdef DEBUG
    printf("[DEBUG]: cmd name: < %s >\n", p_cmd_name);
#endif

    strcpy(pcmd->cmd_name, p_cmd_name);

    for(;;)
    {   
        // 获取分割之后的字符串地址
        p_cmd_arg = strtok(NULL, " ");
        if (p_cmd_arg == NULL)
            break;
        // 将字符串拷贝到结构体中
        strcpy(pcmd->cmd_arg_list[index++], p_cmd_arg);
    }
    //存储参数的个数
    pcmd->cmd_arg_count = index;

    return 0;
}

/* 命令分发 */
int cmd_dispatch(cmd_t *pcmd)
{
    if (pcmd == NULL)
        return -1;

    if (strcmp(pcmd->cmd_name, "ls") == 0)
    {
        // 调用ls命令处理模块
#ifdef DEBUG
        printf("ls command handle.\n");
#endif
    }
    else if (strcmp(pcmd->cmd_name, "cp") == 0)
    {
        // 调用cp命令处理模块
#ifdef DEBUG
        printf("cp command handle.\n");
#endif
    }
}