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
#include <pthread.h>

#define LOGIN_SUCCESS 1
#define LOGIN_FAILURE 0

typedef struct
{
    char *ip;
    unsigned char flag;
    struct sockaddr_in *peer_addr;
} thread_type;

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
}

void *message_thread(void *arg)
{
    thread_type *pocket = (thread_type *) arg;

    int new_sockfd;

    // 1.给用户回复的密钥正确
    char *ip = pocket->ip;
    unsigned char login_flag = pocket->flag;
    struct sockaddr_in *addr = pocket->peer_addr;

    // 创建新的套接字和端口准备通信
    new_sockfd = init_socket(ip, "0");
    sendto(new_sockfd, &login_flag, sizeof(login_flag), 0, (struct sockaddr *)addr, sizeof(struct sockaddr));

    // 接收数据
    recv_data(new_sockfd);

    pthread_exit(NULL);
}

void user_login(const char *ip, const char *port)
{
    int sockfd;
    int n = 0;
    char buf[20] = {0};
    struct sockaddr_in client_addr;
    int len = sizeof(client_addr);
    unsigned char login_flag;
    pthread_t tid;
    thread_type pocket;

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
            pocket.flag = login_flag;
            pocket.ip = (char *)ip;
            pocket.peer_addr = &client_addr;

            // 创建子线程,子线程准备接收当前用户的数据,主线程负责接收用户的密钥
            pthread_create(&tid, NULL, message_thread, (void *)&pocket);
        }
        // 密钥失败
        else
        {
            // 给客户端回复-登陆失败
            sendto(sockfd, &login_flag, sizeof(login_flag), 0, (struct sockaddr *)&client_addr, len);
        }

        // 线程设置为分离式,子线程结束后,系统自动回收资源
        pthread_detach(tid);
    }
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

    // 1.接收用户的密钥，准备登录
    user_login(argv[1], argv[2]);

    // 2.接收数据
    // recv_data(sockfd);

    // 3.关闭文件描述符
    close(sockfd);

    return 0;
}
