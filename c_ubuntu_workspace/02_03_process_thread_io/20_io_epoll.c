#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>

#define MAXEVENTS 10

int main()
{
    int epfd, ret;
    struct epoll_event ev;//请求事件结构体
    struct epoll_event ret_ev[MAXEVENTS];
    char buffer[64] = {0};

    epfd = epoll_create(1);
    if (epfd == -1)
    {
        perror("[ERROR] epoll_create(): ");
    }

    printf("epfd = %d\n", epfd);

    // 设置文件描述符
    ev.data.fd = 0;
    // 设置事件
    ev.events = EPOLLIN;

    // epoll_ctl() 的作用是在 epoll 实例中对某个文件描述符执行操作。
    // 它用于将文件描述符添加到 epoll 实例中、修改已存在的文件描述符、或者从 epoll 实例中删除文件描述符。
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, 0, &ev);
    if (ret == -1)
    {
        perror("[ERROR] epoll_ctl(): ");
        exit(EXIT_FAILURE);
    }

    for(;;)
    {
        // 等待文件描述符关联的事件发生
        ret = epoll_wait(epfd, ret_ev, MAXEVENTS, 1000);
        if (ret == -1)
        {
            perror("[ERROR] epoll_wait(): ");
            exit(EXIT_FAILURE);
        }
        else if(ret == 0)
        {
            printf("TImeout\n");
        }
        else if (ret > 0)
        {
            int i ;
            for (i = 0; i < ret; i++)
            {
                // 判断是否为标准输入文件描述符
                if (ret_ev[i].data.fd == 0)
                {
                    fgets(buffer, sizeof(buffer), stdin);
                    printf("buffer: %s\n", buffer);
                }
            }
        }
    }


    return 0;
}
