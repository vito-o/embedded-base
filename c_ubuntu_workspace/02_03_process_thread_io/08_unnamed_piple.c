#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int cpid = 0;
    int ret;
    int pipefd[2];
    size_t rbytes, wbytes;

    ret = pipe(pipefd);
    if (ret == -1) 
    {
        perror("error pipe(): ");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1) 
    {
        perror("error fork(): ");
        exit(EXIT_FAILURE);
    }

    // 子进程
    if (cpid == 0)
    {
        char buffer[1024] = {0};
        close(pipefd[1]);   //关闭写管道（用不到）

        // 没有读到数据时，会阻塞
        rbytes = read(pipefd[0], buffer, sizeof(buffer));
        if(rbytes == -1)
        {
            perror("error read(): ");
            exit(EXIT_FAILURE);
        }
        printf("the pip read info is : %s\n", buffer);

        close(pipefd[0]);   //关闭读管道 (执行完毕)
        exit(EXIT_SUCCESS);
    }
    // 父进程
    else 
    {
        close(pipefd[0]);   //关闭读管道 (执行完毕)

        char info[] = "hello, pipe";

        wbytes = write(pipefd[1], info, sizeof(info));
        if(wbytes == -1)
        {
            perror("error write(): ");
            exit(EXIT_FAILURE);
        }

        close(pipefd[1]);   //关闭写管道（用不到）
        wait(NULL);
        exit(EXIT_SUCCESS);
    }

    return 0;
}
