#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    int fd;

    if (argc != 2)    
    {
        fprintf(stderr, "Usage: <%s>\n", argv[0]);
        return -1;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("open():");
        return -1;
    }

    printf("fd = %d\n", fd);

    close(fd);

    return 0;
}
