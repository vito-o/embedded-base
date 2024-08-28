#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    /*
        pipe(pipefd)调用成功后，会为你创建一对文件描述符，并将它们存储在pipefd数组中：
        pipefd[0]是用于读取的文件描述符。
        pipefd[1]是用于写入的文件描述符。
    
    */    
    int pipefd[2];
    pid_t cpid;
    char buf;

    if (argc != 2)
    {
        fprintf(stderr, "%s:请填写需要传递的信息\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pipe(pipefd) == -1)
    {
        perror("创建管道失败\n");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1)
    {
        perror("邀请新学员失败！\n");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0)
    {
        // 新学员读数据 关闭写端
        close(pipefd[1]);
        char str[100] = {0};
        sprintf(str, "新学员%d 收到邀请\n", getpid());
        write(STDOUT_FILENO, str, sizeof(str));
        // 一直读取读端的数据 单个字节读取方便读取结尾 直到数据结束或出错
        while (read(pipefd[0], &buf, 1) > 0)
        {
            // 将读取数据写到标准输出
            write(STDOUT_FILENO, &buf, 1);
        }
        // 输出换行
        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        // 老学员写数据 关闭读端
        close(pipefd[0]);
        // 写入传入的参数到管道的写端
        printf("老学员%d 发出邀请\n", getpid());
        write(pipefd[1], argv[1], strlen(argv[1]));
        // 写完之后关闭写段 读端会返回0
        close(pipefd[1]);
        // 等待子进程结束
        waitpid(cpid, NULL, 0);
        exit(EXIT_SUCCESS);
    }

    return 0;
}
