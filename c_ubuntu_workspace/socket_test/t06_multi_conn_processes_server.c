#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#define handle_error(cmd, result)   \
    if (result < 0)                 \
    {                               \
        perror(cmd);                \
        return -1;                  \
    }


void zombie_dealer(int sig)
{
    pid_t pid;
    int status;
    // 一个SIGCHLD可能对应多个子进程的退出
    // 使用while循环回收所有退出的子进程，避免僵尸进程的出现
    while((pid = waitpid(-1, &status, WNOHANG)) > 0)
    {
        if (WIFEXITED(status))
        {
            printf("子进程：%d 以 %d 状态正常退出，以被回收\n", pid, WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("子进程: %d 被 %d 信号杀死，已被回收\n", pid, WTERMSIG(status));
        }
        else 
        {
            printf("子进程: %d 因其它原因退出，已被回收\n", pid);
        }
    }
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

    // 注册信号处理函数，处理SIGCHLD信号，避免僵尸进程出现
    signal(SIGCHLD, zombie_dealer);


    // 接受client连接
    while(1)
    {
        int client_fd = accept(sockfd, (struct sockaddr *)&client_addr, &cliaddr_len);
        handle_error("accept", client_fd);

        pid_t pid = fork();

        if (pid > 0)
        {
            printf("this is father, pid is %d, continue accepting...\n", getpid());

            // 父进程不需要处理client_fd，释放文件描述符，使其引用技术减一
            // 以便子进程释放client_fd后，其引用计数可以减为0,从而释放资源
            close(client_fd);
        }
        else if (pid == 0)
        {
            // 子进程不需要处理sockfd，释放文件描述符，使其引用计数减一
            close(sockfd);


            printf(
                "与客户端 from %s at PORT %d 文件描述符 %d 建立连接\n",
                inet_ntoa(client_addr.sin_addr),//ip地址
                ntohs(client_addr.sin_port),    //端口
                client_fd
            );
            printf("新的服务端pid为: %d\n", getpid());
            // 读取客户端数据，并打印到stdout
            read_from_client_then_write((void *)&client_fd);

            // 释放资源并终止子进程
            close(client_fd);
            exit(EXIT_SUCCESS);
        }

    }

    printf("释放资源\n");
    close(sockfd);

    return 0;
}