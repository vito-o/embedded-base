#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int num = 0;

int main(int argc, char const *argv[])
{
    __pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0)
    {
        num = 1;
        printf("子进程num的值是： %d\n", num);
    } else {
        sleep(1);
        printf("父进程num的值是： %d\n", num);
    }
    



    return 0;
}
