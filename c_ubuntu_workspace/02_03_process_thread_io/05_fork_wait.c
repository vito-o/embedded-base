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

        // 会阻塞父进程，等到子进程状态变化，自动释放资源并返回
        pid_t rcpid = wait(&status);
        if (rcpid == -1)
        {
            fprintf(stderr, "[error wait(): ]");
            exit(EXIT_FAILURE);
        }

        printf("rcpid = %d, exit code = %d\n", rcpid, WEXITSTATUS(status));
    }

    return 0;
}
