#include <stdio.h>
#include <sys/types.h>	       /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
// 多进程udp 客户端和服务端
#define LOGIN_SUCCESS 1
#define LOGIN_FAILURE 0

int init_socket(const char *ip, const char *port)
{
    int sockfd;
    struct sockaddr_in my_addr;

    // 1.通过socket创建文件描述符
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("Fail to socket(): ");
        exit(EXIT_FAILURE);
    }

    // 2.填充服务器自己的ip + port
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = inet_addr(ip);
    my_addr.sin_port = htons(atoi(port));

    printf("ip = %s\n",ip);
    printf("port = %s\n",port);

    // 3.把ip + port与socket绑定
    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0)
    {
        perror("Fail to bind(): ");
        exit(EXIT_FAILURE);
    }

    printf("wait recv data: \n");

    return sockfd;
}

int user_login(const char *ip, const char *port)
{
    int sockfd;
    int n = 0;
    char buf[20] = {0};
    struct sockaddr_in client_addr;
    int len = sizeof(client_addr);
    unsigned char login_flag;
    int new_sockfd;

    // 创建套接字
    sockfd = init_socket(ip, port);

    while (1)
    {
        memset(buf, 0, sizeof(buf));
        n = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, &len);
        if (n < 0)
        {
            perror("Fail to recvfrom: ");
            exit(EXIT_FAILURE);
        }

        printf("key = %s\n", buf);

        login_flag = (strncmp(buf, "root", 4) == 0) ? LOGIN_SUCCESS : LOGIN_FAILURE;

        // 此时说明密钥正确
        if (login_flag == LOGIN_SUCCESS)
        {
            // 创建子进程,准备数据的交互
            if (fork() == 0)
            {
                close(sockfd);

                // 绑定0号端口,系统会随机分配一个可用的端口
                new_sockfd = init_socket(ip, "0");

                // 给客户端的回复 -- 登录成功
                sendto(new_sockfd, &login_flag, sizeof(login_flag), 0, (struct sockaddr *)&client_addr, len);

                break;
            }
        }
        // 密钥失败
        else
        {
            // 给客户端回复-登陆失败
            sendto(sockfd, &login_flag, sizeof(login_flag), 0, (struct sockaddr *)&client_addr, len);
        }
    }
    
    return new_sockfd;
}

void recv_data(int new_sockfd)
{
    int n = 0;
    char buf[1024] = {0};
    struct sockaddr_in client_addr;
    int len = sizeof(client_addr);

    while (1)
    {
        memset(buf,0,sizeof(buf));
		n = recvfrom(new_sockfd,buf,sizeof(buf),0,(struct sockaddr *)&client_addr,&len);
        if (n < 0)
        {
            perror("Fail to recvfrom(): ");
            exit(EXIT_FAILURE);
        }

        printf("============================\n");
		printf("Recv from IP = %s\n",inet_ntoa(client_addr.sin_addr));
		printf("Recv from Port = %d\n",ntohs(client_addr.sin_port));
		printf("Recv %d bytes : %s\n",n,buf);

		if(strncmp(buf,"quit",4) == 0)
			break;
    }

    close(new_sockfd);
    
    exit(EXIT_SUCCESS);
}

void sig_handler(int signum)
{
    waitpid(-1, NULL, WNOHANG);
    printf("recv signum = %d zombie\n", signum);
}

// ./a.out 192.168.239.111 8080
int main(int argc, char const *argv[])
{
    int sockfd;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s ip port!\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // 0.主进程回收僵尸态子进程
    if (signal(SIGCHLD, sig_handler) == SIG_ERR)
    {
        perror("Fail to signal(): ");;
        exit(EXIT_FAILURE);
    }

    // 1.接收用户的密钥，准备登录
    sockfd = user_login(argv[1], argv[2]);

    // 2.接收数据
    recv_data(sockfd);

    // 3.关闭文件描述符
    close(sockfd);

    return 0;
}
