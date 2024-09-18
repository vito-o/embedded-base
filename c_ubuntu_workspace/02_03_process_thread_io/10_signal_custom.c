#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void do_sig_usr(int sig) 
{
    printf(" Receive %s \n",strsignal(sig));
}

int main()
{
    // 设置信号处理方式
    if (signal(SIGUSR1,do_sig_usr) == SIG_ERR)
    {
        perror("signal(): ");
		exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("[error] fork(): ");
        exit(EXIT_FAILURE);
    }

    // 子进程
    if (pid == 0) 
    {
        printf("Child Process < %d > start.\n",getpid());

        // 等待信号唤醒,这里需要信号到达之前进入睡眠状态
        pause();

        exit(EXIT_SUCCESS);
    }
    // 父进程
    else
    {
        sleep(1);

        printf("main is running...\n");

        kill(pid,SIGUSR1);// 给子进程发送 SIGUSR1 信号

        wait(NULL);// 等待子进程退出

        printf("main is end...\n");

        exit(EXIT_SUCCESS);
    }

    return 0;
}
