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
        fprintf(stdout,"\tchild %d running.\n",getpid());

        // SIGSTOP 暂停一个进程，不能阻塞 处理或忽略 只能采用默认操作
        raise(SIGSTOP);
        
        fprintf(stdout,"\t child %d exit \n",getpid());

        while (1)
        {
            /* code */
        }
        

        exit(EXIT_SUCCESS);
    }
    // 父进程
    else
    {
        sleep(1);

        int ret;


        // fprintf(stdout,"father 进程唤醒 子进程\n");
        // kill(pid, SIGCONT);        
        // sleep(1);

        // 给指定进程发送 SIGKILL 信号
        ret = kill(pid, SIGKILL);
        if(ret == 0){
         	fprintf(stdout,"father %d killed child %d\n",getpid(),pid);
        }

        // 等待子进程退出
        waitpid(pid, NULL, 0);

        fprintf(stdout,"father %d exit\n",getpid());

        exit(EXIT_SUCCESS);
    }

    return 0;
}
