#include <stdio.h>
#include <sys/types.h>	       /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void send_data(int sockfd, struct sockaddr_in *addr, int len)
{
    int n = 0;
    char buf[1024] = {0};

    while(1)
    {
        putchar('>');
        memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),stdin);
        buf[strlen(buf) - 1] = '\0'; // '\n' -> '\0'

        // n = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)addr, len);
        n = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)addr, len);
        if (n < 0)
        {
            perror("Fail to sendto");
            exit(EXIT_FAILURE);
        }

        if (strncmp(buf, "quit", 4) == 0)
            break;
    }
}

// ./a.out 192.168.239.1 8080
int main(int argc, char const *argv[])
{
    int sockfd;
    struct sockaddr_in peer_addr;
    int len = sizeof(peer_addr);
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s ip port !\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // 1.通过socket创建文件描述符
    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if (sockfd < 0)
    {
        perror("Fail to socket!");
        return -1;
    }

    // 2.填充服务器的ip + port
    memset(&peer_addr,0,sizeof(peer_addr));
	peer_addr.sin_family = AF_INET;
	peer_addr.sin_port = htons(atoi(argv[2]));
	peer_addr.sin_addr.s_addr = inet_addr(argv[1]);

    // 3.发送数据
    send_data(sockfd, &peer_addr, len);

    // 4.关闭文件描述符
    close(sockfd);

    return 0;
}
