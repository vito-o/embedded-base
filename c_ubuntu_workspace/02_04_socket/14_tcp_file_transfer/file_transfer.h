#ifndef __FILE_TRANSFER_H__
#define __FILE_TRANSFER_H__

#include "tcpsocket.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FILENAME_SZ 256

/*
    |file protocol header|file data|
*/
typedef struct file_protocol {
    size_t filesize;            // 文件大小
    char filename[FILENAME_SZ]; // 文件名
} file_protocol_t;

/* 接收协议头信息 */
extern int recv_protocol_head(int cfd, file_protocol_t *p_head);

/* 接收文件数据并写入到本地文件中 */
extern int recv_filedata(int cfd, const char *filename, size_t targetsize);

/* 服务器接收客户端上传文件的协议信息与文件数据 */
extern int client_upload_file(int cfd);

/* 客户端发送协议头信息给服务器 */
extern int send_protocol_head(const char *filename, int sockfd);

/* 客户端发送协议信息与文件数据给服务器 */
extern int upload_file(const char *filename, int sockfd);

#endif