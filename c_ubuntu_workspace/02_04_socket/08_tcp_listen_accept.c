#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>	       /* See NOTES */
#include <sys/socket.h>

#define BACKLOG 10

int main(int argc, char const *argv[])
{
    
    int sfd, ret, cfd;
    struct sockaddr_in svr_addr, cli_addr;
    socklen_t len = sizeof(struct sockaddr_in);

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s < ip > < port > .\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // 创建套接字
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1)
    {
        perror("[ERROR] Failed to socket.");
        exit(EXIT_FAILURE);
    }

    // 赋值
    bzero(&svr_addr, sizeof(struct sockaddr_in));
    svr_addr.sin_family = AF_INET;
    svr_addr.sin_addr.s_addr = inet_addr(argv[1]);
    svr_addr.sin_port = htons(atoi(argv[2]));

    // 绑定ip地址与端口号
    ret = bind(sfd, (const struct sockaddr *)&svr_addr, sizeof(struct sockaddr_in));
    if (ret == -1)
    {
        perror("[ERROR] Failed to bind.");
        exit(EXIT_FAILURE);
    }

    // 建立监听队列
    ret = listen(sfd, BACKLOG);
    if (ret == -1)
    {
        perror("[ERROR] Failed to listen.");
        exit(EXIT_FAILURE);
    }

    // 接收连接
    cfd = accept(sfd, (struct sockaddr *)&cli_addr, &len);
    if (ret == -1)
    {
        perror("[ERROR] Failed to accept.");
        exit(EXIT_FAILURE);
    }

    printf("ip : %s port : %d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

    for(;;);

    close(sfd);

    return 0;
}
