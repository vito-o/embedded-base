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

    // 打开有名管道用于写入
    fd = open(pipe_path, O_RDONLY);
    if (fd == -1)
    {
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    char write_buf[100];
    ssize_t read_num;

    while ((read_num = read(fd, write_buf, 100)) > 0)
    {
        write(STDOUT_FILENO, write_buf, read_num);
    }

    if (read_num < 0)
    {
        perror("read");
        printf("命令行数据读取异常, 退出");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("接收管道退出，进程种植\n");
    close(fd);

    return 0;
}
