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
        printf("Child A process start < %d >", getpid());
        sleep(2);
        // exit(EXIT_SUCCESS); //终止进程，刷新缓冲区(刷新缓冲区:当类似printf中的打印不带换行符‘\n’时，不会被打印出来，)
        _exit(EXIT_SUCCESS);
        printf("Child A process end < %d >\n", getpid());
        // _exit(EXIT_SUCCESS) //系统调用，终止进程，不会刷新缓冲区
        //正常代码，不写exit，代码执行完毕后，系统会自动调用exit进行刷新缓冲区。
    }
    else if (cpid > 0)
    {
       
    }

    return 0;
}


// 子进程自己申请的资源，由exit函数释放
// 在创建子进程过程中产生的资源，由父进程释放