#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    int fd;
    char *pipe_path = "/tmp/myfifo";

    // 创建有名管道，权限设置为0664
    if (mkfifo(pipe_path, 0664) != 0)
    {
        perror("mkfifo failed");
        if (errno != 17) 
        {
            exit(EXIT_FAILURE);
        }
    }

    // 打开有名管道用于写入
    fd = open(pipe_path, O_WRONLY);
    if (fd == -1)
    {
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    char write_buf[100];
    ssize_t read_num;

    while ((read_num = read(STDIN_FILENO, write_buf, 100)) > 0)
    {
        write(fd, write_buf, read_num);
    }

    if (read_num < 0)
    {
        perror("read");
        printf("命令行数据读取异常, 退出");
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    printf("发送管道退出，进程终止\n");
    close(fd);

    // 释放管道
    // 清除对应的特殊文件
    if (unlink(pipe_path) == -1)
    {
        perror("unlink");
    }

    return 0;
}
