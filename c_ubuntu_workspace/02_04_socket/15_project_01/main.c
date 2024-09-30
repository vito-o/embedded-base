#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>

#include "camera.h"


int main(int argc, char const *argv[])
{
    int cam_fd = init_camera("/dev/video0");
    if (-1 == cam_fd)
    {
        perror("init_camera() failure!");
        return -1;
    }

    if (-1 == init_mmap(cam_fd))
    {
        perror("init_mmap() failure!");
        return -1;
    }

    start_camera(cam_fd);

    // 设置一个时间值，用于指定超时的时间限制
    // timeval 结构体通常包含两个字段，分别表示秒和微秒。
    struct timeval tv;
    tv.tv_sec = 20; // 秒数
    tv.tv_usec = 0; // 微秒

    // 定义一个文件描述符集 fds，用于管理多个文件描述符的集合。
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(cam_fd, &fds);   // 将摄像头设备的文件描述符 cam_fd 添加到 fds 集合中，以便监视

    // 使用 select 函数等待摄像头设备准备好数据（即有可读取的帧），并在准备好时读取这些数据。
    // 等待直到 cam_fd 准备好读取数据，或超时（20秒）。select 函数返回可读文件描述符的数量。

    // 这段代码实现了对摄像头设备的监控，等待新帧的到来。如果在 20 秒内没有新帧
    // 通过 select 机制，程序能够有效地管理 I/O 操作，避免阻塞。
    int r = select(cam_fd + 1, &fds, NULL, NULL, &tv);
    if (0 == r)
    {
        printf("no frame for read!\n");
        return 0;
    }
    else 
    {
        // 如果 select 返回值大于 0，检查 cam_fd 是否在 fds 中，表示有数据可以读取。
        if (FD_ISSET(cam_fd, &fds))
        {
            if (-1 == read_camera(cam_fd))
            {
                printf("read_camera() failure!\n");
                return -1;
            }
        }
    }

    return 0;
}
