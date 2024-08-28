#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int fd;
    ssize_t rbytes = 0;
    ssize_t wbytes = 0;
    char buffer[64] = { 0 };
    char wbuffer[] = "ABCDE12345";

    if (argc != 2)    
    {
        fprintf(stderr, "Usage: <%s> <pathname>\n", argv[0]);
        return -1;
    }

    fd = open(argv[1], O_RDWR|O_CREAT);
    if (fd == -1)
    {
        perror("open():");
        return -1;
    }

    wbytes = write(fd, wbuffer, strlen(wbuffer));
    if (wbytes == -1)
    {
        perror("write():");
        return -1;
    }

    // 將文件的偏移設置位0(从头开始)
    lseek(fd, 0, SEEK_SET);

    rbytes = read(fd, buffer, 10);
    if (rbytes == -1)
    {
        perror("read()");
        return -1;
    }

    printf("buffer : %s\n", buffer);

    close(fd);
    return 0;
}
