#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/*
父子进程并发执行，子进程时从fork之后开始执行的，父子进程fork之后的执行顺序并不一定，有时候父进程先执行完，然后子进程才执行完毕，有时候又反过来。
父子进程的执行顺序由操作系统算法决定的，不是由程序本身决定的。

在fork时，子进程会拷贝父进程的地址空间，包括缓冲区也会拷贝

fputs，的数据不带\n,会将数据现放入缓存中，fork后...  , 打印出3个hello

*/
int main(int argc, char const *argv[])
{

    pid_t cpid;

    write(1, "hello ", 5);
    fputs("hello ", stdout);

    cpid = fork();

    if (cpid == -1)
    {
        perror("fork(): ");
        return -1;
    }

    /* code */
    return 0;
}
