#include "tcpsocket.h"
#include "debug.h"

#define BACKLOG 10

// 用于创建tcp server socket
int create_tcp_server_socket(const char *ip, unsigned short port)
{
    int sfd, ret;
    struct sockaddr_in svr_addr;
    socklen_t len = sizeof(struct sockaddr_in);

    // 创建套接字
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1)
    {
        DEBUG_INFO("[ERROR] Failed to socket: %s\n", strerror(errno));
        return -1;
    }

    // 赋值
    bzero(&svr_addr, sizeof(struct sockaddr_in));
    svr_addr.sin_family = AF_INET;
    svr_addr.sin_addr.s_addr = inet_addr(ip);
    svr_addr.sin_port = htons(port);

    // 绑定ip地址与端口号
    ret = bind(sfd, (const struct sockaddr *)&svr_addr, sizeof(struct sockaddr_in));
    if (ret == -1)
    {
        DEBUG_INFO("[ERROR] Failed to bind: %s\n", strerror(errno));
        return -1;
    }

    // 建立监听队列
    ret = listen(sfd, BACKLOG);
    if (ret == -1)
    {
        DEBUG_INFO("[ERROR] Failed to listen: %s\n", strerror(errno));
        return -1;
    }

    return sfd;
}

// 用于创建tcp client socket
int create_tcp_client_socket(const char *svr_ip, unsigned short svr_port)
{
    int sfd, ret;
    struct sockaddr_in svr_addr;

    // 创建套接字
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1)
    {
        DEBUG_INFO("[ERROR] Failed to socket: %s\n", strerror(errno));
        return -1;
    }

    // 将一段内存区域清零，即将这段内存区域中的所有字节都设置为0。
    bzero(&svr_addr, sizeof(struct sockaddr_in));
    svr_addr.sin_family = AF_INET;
    svr_addr.sin_port = htons(svr_port);
    svr_addr.sin_addr.s_addr = inet_addr(svr_ip);
    // 连接服务端
    ret = connect(sfd, (const struct sockaddr *)&svr_addr, sizeof(struct sockaddr_in));
    if (ret == -1)
    {
        DEBUG_INFO("[ERROR] Failed to connect: %s\n", strerror(errno));
        return -1;
    }

    return sfd;
}

// 用于与客户端建立连接
int wait_for_connect(int sockfd, struct sockaddr_in *cli_addr)
{   
    int cfd;
    socklen_t len = sizeof(struct sockaddr_in);
    // 接收连接
    cfd = accept(sockfd, (struct sockaddr *)cli_addr, &len);
    if (cfd == -1)
    {
        DEBUG_INFO("[ERROR] Failed to accept: %s\n", strerror(errno));
        return -1;
    }
    return cfd;
}

// 显示连接客户端的地址信息
void show_tcp_network_address(struct sockaddr_in *sockaddr)
{
    printf("ip : %s\n",inet_ntoa(sockaddr->sin_addr));
	printf("port : %d\n",ntohs(sockaddr->sin_port));
}

/* 发送数据 */
ssize_t tcp_send_pack(int sockfd, void *buf, size_t len)
{
    return send(sockfd, buf, len, 0);
}

/* 接收数据 */
ssize_t tcp_recv_pack(int sockfd, void *buf, size_t len)
{
    return recv(sockfd, buf, len, 0);
}