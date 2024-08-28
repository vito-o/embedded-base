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


void *read_from_client_then_write(void *argv)
{
    int client_fd = *(int *) argv;

    ssize_t count, send_count = 0;
    char *read_buf = NULL;
    char *write_buf = NULL;

    read_buf = malloc(sizeof(read_buf) * 1024);
    if (!read_buf)
    {
        printf("服务端读缓存创建异常，断开连接\n");
        shutdown(client_fd, SHUT_WR);
        close(client_fd);
        perror("malloc server read_buf");
        return NULL;
    }

    write_buf = malloc(sizeof(write_buf) * 1024);
    if (!write_buf)
    {
        printf("服务端写缓存创建异常，断开连接\n");
        shutdown(client_fd, SHUT_WR);
        close(client_fd);
        perror("malloc server write_buf");
        return NULL;
    }

    while ((count = recv(client_fd, read_buf, 1024, 0)))
    {
        if (count < 0)
        {
            perror("recv");
        }
        printf("receive message from client_fd: %d: %s\n", client_fd, read_buf);

        strcpy(write_buf, "received~\n");
        send_count = send(client_fd, write_buf, 1024, 0);
        if (send_count < 0)
        {
            perror("send");
        }
    }

    printf("客户端client_fd: %d请求关闭连接......\n", client_fd);
    strcpy(write_buf, "receive your shutdown signal\n");

    send_count = send(client_fd, write_buf, 1024, 0);
    if (send_count < 0)
    {
        perror("send");
    }
    
    printf("释放client_fd: %d 资源\n", client_fd);
    shutdown(client_fd, SHUT_WR);
    close(client_fd);

    free(read_buf);
    free(write_buf);

    return NULL;
}


int main(int argc, char const *argv[])
{
    int sockfd, temp_result;
    struct sockaddr_in server_addr, client_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    // 声明通信协议
    server_addr.sin_family = AF_INET;
    // 我们需要绑定0.0.0.0地址，转换成网络字节序列后完成设置
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // 端口设置
    server_addr.sin_port = htons(6666);

    // 创建server socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    handle_error("socket", sockfd);

    // 绑定地址
    temp_result = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    handle_error("bind", temp_result);

    // 进入监听
    temp_result = listen(sockfd, 128);
    handle_error("listen", temp_result);

    socklen_t cliaddr_len = sizeof(client_addr);

    // 接受client连接
    while(1)
    {
        int client_fd = accept(sockfd, (struct sockaddr *)&client_addr, &cliaddr_len);
        handle_error("accept", client_fd);

        printf(
            "与客户端 from %s at PORT %d 文件描述符 %d 建立连接\n",
            inet_ntoa(client_addr.sin_addr),//ip地址
            ntohs(client_addr.sin_port),    //端口
            client_fd
        );

        pthread_t pid_read_write;

        // 启动一个子线程，用来读取客户端数据，并打印到stdout
        // 要注意，此处的pid_read_write并不是线程id，而是用于线程处理函数的标识符
        if(pthread_create(&pid_read_write, NULL, read_from_client_then_write, (void *)&client_fd))
        {
            perror("pthread_create");
        }

        // 将子线程处理为detached状态，使其终止时自动回收资源，同时不阻塞主线程
        pthread_detach(pid_read_write);
        printf("创建子线程并处理为detached状态\n");
    }

    printf("释放资源\n");
    close(sockfd);

    return 0;
}