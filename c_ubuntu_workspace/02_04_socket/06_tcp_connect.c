#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>	       /* See NOTES */
#include <sys/socket.h>

// ./a.out ip port
int main(int argc, char const *argv[])
{
    int sfd, ret;
    struct sockaddr_in svr_addr;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s < ip > < port >.\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // 创建套接字
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1)
    {
        perror("[ERROR] Failed to socket.");
        exit(EXIT_FAILURE);
    }

    // 将一段内存区域清零，即将这段内存区域中的所有字节都设置为0。
    bzero(&svr_addr, sizeof(struct sockaddr_in));
    svr_addr.sin_family = AF_INET;
    svr_addr.sin_port = htons(atoi(argv[2]));
    svr_addr.sin_addr.s_addr = inet_addr(argv[1]);
    // 连接服务端
    ret = connect(sfd, (const struct sockaddr *)&svr_addr, sizeof(struct sockaddr_in));
    if (ret == -1)
    {
        perror("[ERROR] Failed to connect.");
        exit(EXIT_FAILURE);
    }

    sleep(1);

    close(sfd);
    return 0;
}
