#include "file_transfer.h"
#include "debug.h"

/* 接收协议头信息 */
int recv_protocol_head(int cfd, file_protocol_t *p_head)
{
    ssize_t rbytes = 0;
    ssize_t total_received = 0;
    char *buffer = (char *)p_head;

    for(;;)
    {
        rbytes = tcp_recv_pack(cfd, buffer + total_received, sizeof(file_protocol_t) - total_received);
        if (rbytes == -1)
        {
            DEBUG_INFO("[ERROR] : %s\n", strerror(errno));
            return -1;
        }
        else if (rbytes == 0)
        {
            DEBUG_INFO("[ERROR] : The client has been shutdown\n");
            break;
        }
        else if (rbytes > 0)
        {
            total_received += rbytes;
            if (total_received == sizeof(file_protocol_t))
                break;
        }
    }

    if (total_received != sizeof(file_protocol_t))
    {
        DEBUG_INFO("[ERROR] : Failed to receive data.\n");
        return -1;
    }

    return 0;
}


/* 接收文件数据并写入到本地文件中 */
int recv_filedata(int cfd, const char *filename, size_t targetsize)
{
    int fd;
    ssize_t rbytes = 0, wbytes = 0, file_size = 0;
    char buffer[1024] = {0};

    printf("filename: %s\n", filename);


    // 1.打开文件
    fd = open(filename, O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if (fd == -1)
    {
        DEBUG_INFO("[ERROR] Failed to open: %s\n", strerror(errno));
        return -1;
    }

    // 2.接收文件数据,并写入到本地文件中
    for(;;)
    {
        rbytes = tcp_recv_pack(cfd, buffer, sizeof(buffer));
        if (rbytes == -1)
        {
            DEBUG_INFO("[ERROR] Failed to tcp_recv_pack: %s\n", strerror(errno));
            return -1;
        }
        else if (rbytes == 0)
        {
            DEBUG_INFO("[INFO] The client has been shutdown.");
            return -1;
        }
        else if (rbytes > 0)
        {
            wbytes = write(fd, buffer, rbytes);
            if (wbytes == -1)
            {
                DEBUG_INFO("[ERROR] Failed to write: %s\n", strerror(errno));
                return -1;
            }

            file_size += rbytes;

            if (file_size == targetsize)
                break;
        }
    }

    close(fd);

    return file_size;
}

/* 服务器接收客户端上传文件的协议信息与文件数据 */
int client_upload_file(int cfd)
{
    int ret, recvsize = 0;
    file_protocol_t head;
    // 1.接收协议头信息
    ret = recv_protocol_head(cfd, &head);
    if (ret == -1)
    {
        return -1;
    }

    // strcpy(head.filename, "./1.png");

    // 接收文件数据
    recvsize = recv_filedata(cfd, head.filename, head.filesize);
    printf("recvsize = %d\n", recvsize);

    return recvsize;
}

/* 客户端发送协议头信息给服务器 */
int send_protocol_head(const char *filename, int sockfd)
{
    int fd, ret;
    int filesize;
    file_protocol_t head;
    // 协议头信息: filename + filesize

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        DEBUG_INFO("[ERROR] Failed to open: %s\n", strerror(errno));
        return -1;
    }

    filesize = lseek(fd, 0, SEEK_END);
    close(fd);

    head.filesize = filesize;
    strcpy(head.filename, filename);
    
    ret = tcp_send_pack(sockfd, &head, sizeof(head));
    if (ret != sizeof(file_protocol_t))
    {
        DEBUG_INFO("[ERROR] Failed to tcp_send_pack: %s\n", strerror(errno));
        return -1;
    }

    return filesize;
}


/* 客户端发送协议信息与文件数据给服务器 */
int upload_file(const char *filename, int sockfd)
{
    int file_size = 0;
    int fd;
    ssize_t rbytes = 0, sbytes = 0;
    char buffer[1024] = {0};
    int upload_size = 0;

    // 1.将协议头信息发送服务器
    file_size = send_protocol_head(filename, sockfd);

    // 2.循环读取文件数据并发送给服务器
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        DEBUG_INFO("[ERROR] Failed to open: %s\n", strerror(errno));
        return -1;
    }

    for(;;)
    {
        rbytes = read(fd, buffer, sizeof(buffer));
        if (rbytes == -1)
        {
            DEBUG_INFO("[ERROR] Failed to read: %s\n", strerror(errno));
            return -1;
        }
        else if (rbytes == 0)
            break;
        
        // 发送数据给服务器
        sbytes = tcp_send_pack(sockfd, buffer, rbytes);
        if (sbytes != rbytes)
        {
            DEBUG_INFO("[ERROR] Failed to read: %s\n", strerror(errno));
            return -1;
        }

        upload_size += rbytes;
    }

    close(fd);

    return upload_size;
}