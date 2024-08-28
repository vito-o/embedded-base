#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>

// 共享内存对象在临时文件系统中的表示位于/dev/shm目录下


int main(int argc, char const *argv[])
{
    char shamName[100] = {0};
    sprintf(shamName, "/letter%d", getpid());
    printf("shamName: %s\n", shamName);

    // 1.创建一个共享内存
    int fd = shm_open(shamName, O_CREAT | O_RDWR, 0644);
    if (fd < 0)
    {
        perror("共享内存对象开启失败\n");
        exit(EXIT_FAILURE);
    }

    while (1);
    return 0;
}
