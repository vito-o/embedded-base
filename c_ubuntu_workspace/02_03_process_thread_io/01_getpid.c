#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
    printf("getpid = %d, getppid = %d \n", getpid(), getppid());
    return 0;
}
