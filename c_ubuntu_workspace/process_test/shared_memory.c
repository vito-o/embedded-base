#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char const *argv[])
{   
    // 1.创建一个共享内存
    char shmName[100] = {0};
    sprintf(shmName, "/letter%d", getpid());
    // sprintf(shmName, "/letter%d", getpid());
    int fd = shm_open(shmName, O_CREAT | O_RDWR, 0644);
    if (fd < 0)
    {
        perror("共享内存对象开启失败\n");
        exit(EXIT_FAILURE);
    }
    

    // 2.设置共享内存对象大小
    ftruncate(fd, 100);

    // 3.内存映射
    char *share = mmap(NULL, 100, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (share == MAP_FAILED)
    {
        perror("共享内存对象映射到内存失败\n");
        exit(EXIT_FAILURE);
    }

    // 映射完成之后  关闭fd连接  不是释放
    close(fd);

    // 4.使用内存映射实现进程间的通信
    // 创建子进程
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("创建子进程失败\n");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) 
    {
        // 子进程写入数据作为回信
        strcpy(share, "你是个好人\n");
        printf("新学员%d完成回信\n", getpid());
    }
    else
    {
        // 父进程等待回信
        waitpid(pid, NULL, 0);
        printf("老学员%d收到了新学员%d的回信:%s",getpid(), pid, share);
        // 5.释放映射区
        munmap(share, 1024);
    }

    // 6.释放共享内存
    shm_unlink(shmName);

    return 0;
}
