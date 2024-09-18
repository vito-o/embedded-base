#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 进程替换，执行execl会将整个当前进程替换位指定的进程，当前进程的资源就没有了

// 进程替换，一般推荐先fork一个子进程，然后再将子进程替换
int main()
{

    int ret;

#if 0
    // ret = execl("/bin/ls", "ls", "-l", NULL);
    // 前面的./app表示路径，后面的./app表示执行app程序
    ret = execl("./app", "./app", NULL);
    if (ret == -1)
    {
        perror("[error] execl(): ");
        exit(EXIT_FAILURE);
    }
    // 替换后，这个打印就不会显示了
    printf("execl....\n");
#endif

    char *const argv[] = { "ls", "-l", NULL };
    ret = execv("/bin/ls", argv);

    /* code */
    return 0;
}
