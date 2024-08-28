#include <errno.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    fopen("/opt", "a+");
    printf("errno: %d\n", errno);
    perror("打开文件出问题");

    return 0;
}
