#ifndef __TCP_SOCKET_H__
#define __TCP_SOCKET_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>	       /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

/* 用于创建tcp server socket */
extern int create_tcp_server_socket(const char *ip, unsigned short port);

/* 用于创建tcp client socket */
extern int create_tcp_client_socket(const char *svr_ip, unsigned short svr_port);

/* 用于与客户端建立连接 */
extern int wait_for_connect(int sockfd, struct sockaddr_in *cli_addr);

/* 显示连接客户端的地址信息 */
extern void show_tcp_network_address(struct sockaddr_in *sockaddr);

/* 发送数据 */
extern ssize_t tcp_send_pack(int sockfd, void *buf, size_t len);

/* 接收数据 */
extern ssize_t tcp_recv_pack(int sockfd, void *buf, size_t len);

#endif