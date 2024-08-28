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


void *read_from_client(void *argv)
{
    int client_fd = *(int *) argv;
    char *read_buf = NULL;
    ssize_t count = 0;

    read_buf = malloc(sizeof(char) * 1024);
    if (!read_buf)
    {
        perror("malloc server read_buf");
        return NULL;
    }

    while((count = recv(client_fd, read_buf, 1024, 0)))
    {
        if (count < 0)
        {
            perror("recv");
        }
        fputs(read_buf, stdout);
    }

    printf("客户端请求关闭连接......\n");
    free(read_buf);
    return NULL;
}

void *write_to_client(void *argv)
{
    int client_fd = *(int *) argv;
    char *write_buf = NULL;

    ssize_t send_count = 0;

    write_buf = malloc(sizeof(char) * 1024);
    if (!write_buf)
    {
        printf("写缓存方配失败，端开连接\n");
        shutdown(client_fd, SHUT_WR);
        perror("malloc server write_buf");
        return NULL;
    }

    while (fgets(write_buf, 1024, stdin) != NULL)
    {
        send_count = send(client_fd, write_buf, 1024, 0);
        if (send_count < 0)
        {
            perror("send");
        }
    }

    printf("接收到命令和的终止信号，不再写入，关闭连接......\n");
    shutdown(client_fd, SHUT_WR);
    free(write_buf);

    return NULL;
}


int main(int argc, char const *argv[])
{
    int sockfd, temp_result, client_fd;
    pthread_t pid_read, pid_write;

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

    // 接收第一个client连接
    socklen_t client_addr_len = sizeof(client_addr);
    client_fd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
    handle_error("accept", client_fd);

    printf(
        "与客户端 from %s at PORT %d 文件描述符 %d 建立连接\n", 
        inet_ntoa(client_addr.sin_addr), 
        ntohs(client_addr.sin_port),
        client_fd
    );

    // 启动一个子线程，用来读取客户端数据，并打印到stdout
    pthread_create(&pid_read, NULL, read_from_client, (void *)&client_fd);
    // 启动一个子线程，用来从命令和读取数据并发送到客户端
    pthread_create(&pid_write, NULL, write_to_client, (void *)&client_fd);

    // 阻塞主线程
    pthread_join(pid_read, NULL);
    pthread_join(pid_write, NULL);

    printf("释放资源\n");
    close(client_fd);
    close(sockfd);

    return 0;
}

