#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    printf("老学员-%d 春暖花开! \n", getpid());
    /*
        不需要传参
        return: int 进程号
            1》：-1 出错
            0》：父进程中表示子进程的PID
        __pid_t fork (void)
    
    */
    pid_t pid = fork();

    // 从fork之后，下面的所有代码都是在父子进程中各自执行一次
    if (pid < 0)
    {
        // 创建新进程失败
        printf("新学员加入失败\n");
    } else if (pid == 0) 
    {
        // 这里往下的代码都是新的子进程执行的
        printf("新学员-%d 加入成功，他是老学员-%d推荐的\n", getpid(), getppid());
    } else {
        // 这里往下的代码都是父进程执行的
        printf("老学员-%d 继续深造，他推荐了%d\n", getpid(), pid);
    }

    return 0;
}
