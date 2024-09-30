#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>	       /* See NOTES */
#include <sys/socket.h>

int main(int argc, char const *argv[])
{
    int sdf, ret;
    ssize_t sbytes = 0, rbytes = 0;
    char buffer[1024] = {0};
    struct sockaddr_in svr_addr;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s < ip > < port >. \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // 创建套接字
    sdf = socket(AF_INET, SOCK_STREAM, 0);
    if (sdf == -1)
    {
        perror("[ERROR] Failed to socket.");
        exit(EXIT_FAILURE);
    }

    bzero(&svr_addr, sizeof(struct sockaddr_in));
    svr_addr.sin_family = AF_INET;
    svr_addr.sin_addr.s_addr = inet_addr(argv[1]);
    svr_addr.sin_port = htons(atoi(argv[2]));

    ret = connect(sdf, (const struct sockaddr *)&svr_addr, sizeof(struct sockaddr_in));
    if (ret == -1)
    {
        perror("[ERROR] Failed to connect");
        exit(EXIT_FAILURE);
    }

    strcpy(buffer, "hello, server");
    // 发送数据
    sbytes = send(sdf, buffer, strlen(buffer)+1, 0);
    if (ret == -1)
    {
        perror("[ERROR] Failed to send");
        exit(EXIT_FAILURE);
    }

    bzero(buffer, sizeof(buffer));
    // 接收数据
    rbytes = recv(sdf, buffer, sizeof(buffer), 0);
    if (ret == -1)
    {
        perror("[ERROR] Failed to recv.");
        exit(EXIT_FAILURE);
    }
    else if (rbytes > 0)
    {
        printf("buffer: %s\n", buffer);
    }
    else if (rbytes == 0)
    {
        printf("The server has been shutdown.\n");
    }

    close(sdf);
    
    return 0;
}
