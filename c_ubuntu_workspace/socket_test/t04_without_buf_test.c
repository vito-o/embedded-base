#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main()
{
    
    FILE *file = fopen("/home/vito/workspace/socket_test/t.txt", "w");
    if (file == NULL)
    {
        perror("fopen");
    }

    // 设置文件为行缓冲模式
    if (setvbuf(file, NULL, _IOLBF, 0) != 0)
    {
        perror("Failed to set buffer mode");
        return 1;
    }

    fprintf(file, "hello\n");
    // fflush(file);

    

    char *argv[] = { "/usr/bin/ping", "-c", "1", "www.baidu.com", NULL };
    char *envp[] = { NULL };
    execve(argv[0], argv, envp);
    perror("execve");


    return 0;
}
