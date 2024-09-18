#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


// 父进程创建多个子进程方式

int main(int argc, char const *argv[])
{
    pid_t cpid;

    cpid = fork();

    if (cpid == -1)
    {
        perror("[ERROR] fork(): ");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0)
    {
        printf("Child A process < %d >\n", getpid());
        sleep(2);
        exit(88);
    }
    else if (cpid > 0)
    {
        int status = 0;

        // -1 会等待任意子进程， 0 默认是阻塞的
        // pid_t rcpid = waitpid(-1, &status, 0);
        
        // WNOHANG 不等待，立即退出
        // pid_t rcpid = waitpid(-1, &status, WNOHANG);
        // if (rcpid == -1)
        // {
        //     fprintf(stderr, "[error wait(): ]");
        //     exit(EXIT_FAILURE);
        // }

        // WNOHANG 不等待，立即退出,可以用循环方式进行等待
        pid_t rcpid = 0;
        // 如果设置 WNOHANG 非阻塞标志，子进程没有返回，则rcpid为0
        while((rcpid = waitpid(-1, &status, WNOHANG)) == 0);
        printf("rcpid = %d, exit code = %d\n", rcpid, WEXITSTATUS(status));
    }

    return 0;
}
