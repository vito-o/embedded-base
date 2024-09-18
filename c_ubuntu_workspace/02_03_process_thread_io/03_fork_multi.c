#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

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
        exit(EXIT_SUCCESS);
    }
    else if (cpid > 0)
    {
        cpid = fork();

        if (cpid == -1)
        {
            perror("[ERROR] fork(): ");
            exit(EXIT_FAILURE);
        }

        if (cpid == 0)
        {
            printf("Child B process < %d >\n", getpid());
            sleep(3);
            exit(EXIT_SUCCESS);
        }
        else if (cpid > 0)
        {
            
        }
    }

    return 0;
}
