#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

// 有名信号量在文件系统的表示
int main(int argc, char const *argv[])
{
    char *sem_name = "/named_sem";

    // 初始化有名信号量
    sem_t *sem = sem_open(sem_name, O_CREAT, 0666, 0);

    pid_t pid = fork();
    if (pid > 0)
    {
        sem_wait(sem);
        printf("this is father\n");

        // 等待子进程执行完毕
        waitpid(pid, NULL, 0);

        // 释放引用
        sem_close(sem);

        // 释放有名信号量
        // if (sem_unlink(sem_name) == -1)
        // {
        //     perror("sem_unlink");
        // }
    }
    else if (pid == 0)
    {
        sleep(1);
        printf("this is son\n");
        sem_post(sem);

        // 释放引用
        sem_close(sem);
    }
    else 
    {
        perror("fork");
    }



    return 0;
}
