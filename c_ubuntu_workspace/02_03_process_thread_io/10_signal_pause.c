#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("[error] fork(): ");
        exit(EXIT_FAILURE);
    }

    // 子进程
    if (pid == 0) 
    {
        sleep(2);

        fprintf(stdout,"\tchild %d running.\n",getpid());

        // kill(getppid(),SIGUSR1);
        // kill(getppid(),SIGCONT);
        exit(EXIT_SUCCESS);
    }
    // 父进程
    else
    {
        sleep(1);

        printf("main is running...\n");

        pause();

        // 不会打印,SIGUSR1 信号的默认动作是终止进程
        fprintf(stdout,"Main Process End.\n"); 

        exit(EXIT_SUCCESS);
    }

    return 0;
}
