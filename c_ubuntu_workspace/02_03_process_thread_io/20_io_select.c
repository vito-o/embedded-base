#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
/*
    使用select进行io多路复用， 单个进程/线程就可以同时处理多个IO请求
    一个进程/线程可以监视多个文件句柄；一旦某个文件句柄就绪，就能够通知应用程序进行相应的读写操作；没有文件句柄就绪时会阻塞应用程序，交出cpu。多路是指网络连接，复用指的是同一个进程/线程。

    代码逻辑

    1.如果3s之后，文件描述符集合中没有任何描述符就绪，就会超时返回
    2.tv时间时会被select修改，一旦超时，时间就被使用完成了，会被赋值了
    3.select每次将就绪文件描述符直接拷贝到原集合中，相当于将没有就绪的文件描述符从集合中删除，如果是超时返回，相当于集合清空了。

*/
int main()
{
    int ret;
    int maxfd = 0;
    fd_set readfds, tmpfds;
    // 设置超时时间位3秒0毫秒
    struct timeval tv = {3, 0}, tmp_tv;
    char buffer[64] = { 0 };

    // 重置readfds
    FD_ZERO(&readfds);
    // 将标准输入读文件描述符放入集合中
    FD_SET(0, &readfds);

    for(;;)
    {
        tmp_tv = tv;
        tmpfds = readfds;

        ret = select(maxfd + 1, &tmpfds, NULL, NULL, &tmp_tv);
        if (ret == -1)
        {
            perror("[ERROR] select(): ");
            exit(EXIT_FAILURE);
        }
        else if(ret == 0)   //超时返回
        {
            printf("timeout\n");
        }
        // ret 大于0, 表示有文件描述符就绪
        else if(ret > 0)
        {
            // 判断标准输入文件描述符是否在就绪集合中，如果在则表示就绪
            if (FD_ISSET(0, &tmpfds)) 
            {
                fgets(buffer, sizeof(buffer), stdin);
                printf("buffer: %s", buffer);
            }
        }
    }



    return 0;
}
