#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char const *argv[])
{
    
    int fd = open("io.txt", O_RDONLY);
    if (fd == -1) 
    {
        perror("open");//会在传入的字符串后面，拼接错误信息。
        exit(EXIT_FAILURE);
    }

    // 创建一个缓冲区来存放读取的数据
    char buffer[1024];
    ssize_t bytes_read;

    /*
        int __fd： 文件描述符
        void *__buf: 存放数据
        size_t __nbytes： 读取数据的长度
        ssize_t read (int __fd, void *__buf, size_t __nbytes)
    */
    while((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) 
    {
        // 将读取的数据写入标准输出
        // 文件描述符类型的 
        // stdin -> 0
        // stdout -> 1
        // stderr -> 2

        /*
            int __fd: 文件描述符
            const void *__buf: 要写出的数据
            size_t __n： 写出的长度
            ssize_t write (int __fd, const void *__buf, size_t __n)
        */
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    if (bytes_read == -1)
    {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);
    return 0;
}
