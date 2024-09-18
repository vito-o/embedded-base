#include <stdio.h>
#include <stdlib.h>
#include <poll.h>

int main()
{
    
    int ret, maxfd = 0;
    struct pollfd pfds;
    char buffer[64] = { 0};
    // pfds.fd = 0; 设置了文件描述符为 0，即标准输入（stdin）。
    pfds.fd = 0;

    // 这行代码的作用是指定在 poll() 系统调用中关注的事件类型。
    // POLLIN 表示该文件描述符（pfds.fd，即标准输入 stdin，文件描述符 0）上有数据可以读取时，poll() 会返回并告诉程序。
    pfds.events = POLLIN;

    maxfd = pfds.fd;

    for(;;)
    {
        ret = poll(&pfds, maxfd+1, 1000);
        if (ret == -1)
        {
            perror("[ERROR] poll(): ");
            exit(EXIT_FAILURE);
        }
        // 超时
        else if (ret == 0)
        {
            printf("TImeout\n");
        }
        else if (ret > 0) 
        {
            // 判断返回的就绪事件是否为POLLIN
            if (pfds.revents & POLLIN)
            {
                // 如果是POLLIN，则表示有用户输入
                fgets(buffer, sizeof(buffer), stdin);
                printf("buffer: %s ", buffer);
            }
        }
    }

    return 0;
}
