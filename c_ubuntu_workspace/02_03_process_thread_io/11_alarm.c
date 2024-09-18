#include <stdio.h>
#include <unistd.h>
#include <string.h>

/*
    定时器的定时任务由内核完成， alarm函数值负责设置定时时间，并告诉内核启动定时器
    当定时时间超时后，内核会向进程发出SIGALRM信号
*/
int main()
{

    unsigned int ret;

    // 设置定时时间位5s的定时器，由内核来进行定时
    // ret 为上一次定时剩余时间
    ret = alarm(5);

    printf("ret = %d\n", ret);  //ret = 0， 前一次设置定时器或者定时器时间已经用完

    ret = alarm(4);

    printf("ret = %d\n", ret);  //ret = 3, 前一次设置定时器或者定时器时间已经用完



    return 0;
}
