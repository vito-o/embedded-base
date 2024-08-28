#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define handle_error(cmd, result)   \
    if (result < 0)                 \
    {                               \
        perror(cmd);                \
        return -1;                  \
    }

int main(int argc, char const *argv[])
{
    int sockfd, temp_result, client_fd;
    struct sockaddr_in server_addr, client_addr;
    char *buf = malloc(1024);

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    // 声明通信协议
    server_addr.sin_family = AF_INET;
    // 我们需要绑定0.0.0.0地址，转换成网络字节序列后完成设置
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // 端口设置
    server_addr.sin_port = htons(6666);


    // 创建server socket，注意通信类型
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    handle_error("socket", sockfd);

    // 绑定地址
    temp_result = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    handle_error("bind", temp_result);

    do
    {
        // 清空缓冲区
        memset(buf, 0, 1024);
        // 尝试接收数据
        socklen_t client_addr_len = sizeof(client_addr);
        temp_result = recvfrom(sockfd, buf, 1024, 0, (struct sockaddr *)&client_addr, &client_addr_len);
        handle_error("recvfrom", temp_result);

        // 如果客户端发来的不是EOF
        if(strncmp(buf, "EOF", 3) != 0)
        {
            printf(
                "received msg from %s at port %d: %s", 
                inet_ntoa(client_addr.sin_addr), 
                ntohs(client_addr.sin_port), 
                buf
            );
            strcpy(buf, "OK\n");
        }
        else
        {
            printf("received EOF from client, existing...\n");
        }

        // 收到数据后回复OK或EOF(客户端发送的是EOF则回复EOF，否则回复OK)
        temp_result = sendto(sockfd, buf, 4, 0, (struct sockaddr *)&client_addr, client_addr_len);
        handle_error("sendto", temp_result);
    } while (strncmp(buf, "EOF", 3) != 0);

    free(buf);

    return 0;
}
