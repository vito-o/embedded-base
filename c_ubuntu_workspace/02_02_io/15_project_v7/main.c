#include <stdio.h>
#include <string.h>
#include "cmd_handle.h"

#define SZ_CMD 64

int main(int argc, char const *argv[])
{
    char command[SZ_CMD] = {0}; //存储 命令缓冲区

    // 主循环
    for(;;)
    {
        printf("TinyShell > ");

        // 从键盘获取输入
        fgets(command, SZ_CMD, stdin);

        // 去掉'\n'
        command[strlen(command)-1] = '\0';  // "ls -l"  ===> "ls -l\n"

        // 退出程序
        if (strncmp(command, "quit", 4) == 0)
        {
            printf("goodBay\n");
            break;
        }

        // 调用cmd_handle模块中的函数，用于执行命令
        cmd_execute(command);
    }


    return 0;
}
