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
    int ret, fd;

    char wbuffer[64] = "fifo pipe.";

    ret = access(FIFO_NAME, F_OK);
    if (ret == -1)
    {
        mkfifo(FIFO_NAME, 0644);
    }



    fd = open(FIFO_NAME, O_RDWR);
    if (fd == -1)
    {
        perror("[ERROR] open(): ");
        exit(EXIT_FAILURE);
    }

    int wbytes = 0;

    wbytes = write(fd, wbuffer, sizeof(wbuffer));
    if (wbytes == -1)
    {
        perror("[ERROR] read(): ");
        exit(EXIT_FAILURE);
    }

    close(fd);

    return 0;
}
