#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// 有名管道会的管道，会在磁盘中显示，但不占用磁盘存储，它用的是内存
#define FIFO_NAME "./fifo"

int main()
{
    int fd;

    fd = open(FIFO_NAME, O_RDWR);
    if (fd == -1)
    {
        perror("[ERROR] open(): ");
        exit(EXIT_FAILURE);
    }

    char buffer[1024] = {0};
    int rbytes = 0;

    rbytes = read(fd, buffer, sizeof(buffer));
    if (rbytes == -1)
    {
        perror("[ERROR] read(): ");
        exit(EXIT_FAILURE);
    }

    printf("buffer: < %s >\n", buffer);

    close(fd);

    return 0;
}
