#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

void do_sig_alarm(int sig)
{
    printf("Receive < %s >\n", strsignal(sig));
}


int main(int argc, char const *argv[])
{
    
    unsigned int ret;

    __sighandler_t sigret;

    sigret = signal(SIGALRM, do_sig_alarm);
    if (sigret == SIG_ERR)
    {
        perror("[ERRPR] signal(): ");
        exit(EXIT_FAILURE);
    }


    ret = alarm(3); // 设置定时时间位3s的定时器，由内核来进行定时

    pause();

    // SIGALRM 信号默认处理方式是结束进程
    printf("Main process end.\n");

    return 0;
}
