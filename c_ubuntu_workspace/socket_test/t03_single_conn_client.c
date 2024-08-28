#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>

#define handle_error(cmd, result)   \
    if (result < 0)                 \
    {                               \
        perror(cmd);                \
        return -1;                  \
    }


void *read_from_server(void *argv)
{
    int sockfd = *(int *) argv;
    char *read_buf = NULL;
    ssize_t count = 0;

    read_buf = malloc(sizeof(char) * 1024);
    if (!read_buf)
    {
        perror("malloc client read_buf");
        return NULL;
    }

    while((count = recv(sockfd, read_buf, 1024, 0)))
    {
        if (count < 0)
        {
            perror("recv");
        }
        fputs(read_buf, stdout);
    }

    printf("收到服务端的终止信号......\n");
    free(read_buf);
    return NULL;
}

void *write_to_server(void *argv)
{
    int sockfd = *(int *) argv;
    char *write_buf = NULL;

    ssize_t send_count = 0;

    write_buf = malloc(sizeof(char) * 1024);
    if (!write_buf)
    {
        printf("写缓存方配失败，端开连接\n");
        shutdown(sockfd, SHUT_WR);
        perror("malloc client write_buf");
        return NULL;
    }

    while (fgets(write_buf, 1024, stdin) != NULL)
    {
        send_count = send(sockfd, write_buf, 1024, 0);
        if (send_count < 0)
        {
            perror("send");
        }
    }

    printf("接收到命令和的终止信号，不再写入，关闭连接......\n");
    shutdown(sockfd, SHUT_WR);
    free(write_buf);

    return NULL;
}


int main(int argc, char const *argv[])
{
    int sockfd, temp_result;
    pthread_t pid_read, pid_write;

    struct sockaddr_in server_addr, client_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));
    // 服务端
    // 声明通信协议
    server_addr.sin_family = AF_INET;
    // 我们需要绑定0.0.0.0地址，转换成网络字节序列后完成设置
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // 端口设置
    server_addr.sin_port = htons(6666);

    // 客户端
    // 声明通信协议
    client_addr.sin_family = AF_INET;
    // 我们需要绑定0.0.0.0地址，转换成网络字节序列后完成设置
    // client_addr.sin_addr.s_addr = htonl(INADDR_LOCAL);
    inet_pton(AF_INET, "192.168.239.111", &client_addr.sin_addr.s_addr);
    // 端口设置
    client_addr.sin_port = htons(8888);



    // 创建socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    handle_error("socket", sockfd);

    // 绑定地址
    temp_result = bind(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr));
    handle_error("bind", temp_result);

    // 连接server
    temp_result = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    handle_error("connect", temp_result);


    // 启动一个子线程，用来读取服务端数据，并打印到stdout
    pthread_create(&pid_read, NULL, read_from_server, (void *)&sockfd);
    // 启动一个子线程，用来从命令和读取数据并发送到服务端
    pthread_create(&pid_write, NULL, write_to_server, (void *)&sockfd);

    // 阻塞主线程
    pthread_join(pid_read, NULL);
    pthread_join(pid_write, NULL);

    printf("释放资源\n");
    close(sockfd);

    return 0;
}

