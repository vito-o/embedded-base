#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>


/*
当子进程结束时，操作系统向父进程发送 SIGCHLD 信号。
父进程捕捉到这个信号后，调用 do_sig_child 函数。
do_sig_child 函数中使用 wait(NULL) 来回收子进程的资源，防止产生僵尸进程。
因此，子进程结束时会调用 do_sig_child 是因为 SIGCHLD 信号的捕捉，而 wait(NULL) 的作用是回收子进程的资源。
*/

void do_sig_child(int sig)
{
    printf("Receive < %s >\n", strsignal(sig));
    wait(NULL); //就不会阻塞，立即释放子进程的资源
}


int main(int argc, char const *argv[])
{
    pid_t cpid;

    __sighandler_t sigret;

    sigret = signal(SIGCHLD, do_sig_child);
    if (sigret == SIG_ERR)
    {
        perror("[ERROR] signal(): ");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1)
    {
        perror("[ERROR] fork(): ");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0)
    {
        printf("CHild process < %d > start.\n", getpid());
        sleep(2);
        exit(EXIT_SUCCESS);
    }
    else if (cpid > 0)
    {
        while (1)
        {
            /* code */
        }
    }

    return 0;
}
