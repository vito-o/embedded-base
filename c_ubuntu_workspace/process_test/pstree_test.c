#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
// 进程树
int main(int argc, char const *argv[])
{
    char *name = "老学员";
    printf("%s %d 在一楼精进\n", name, getpid());

    __pid_t pid = fork();
    if (pid == -1)
    {
        printf("邀请新学员失败\n");
    } else if (pid == 0)
    {
        // 新学员在这里
        char *newName = "ergou";
        char *args[] = {"/home/vito/workspace/process_test/erlou", newName, NULL};
        char *envs[] = {NULL};
        int re = execve(args[0], args, envs);
        if (re == -1)
        {
            printf("新学院上二楼失败\n");
            return -1;
        }
    } else {
        // 老学员在这里
        printf("老学员%d 邀请完%d 之后还是在一楼学习\n", getpid(), pid);
        char bye = fgetc(stdin);
    }
    
    return 0;
}
