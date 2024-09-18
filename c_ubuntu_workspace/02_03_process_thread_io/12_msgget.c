#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define PATHNAME "."
#define PRO_ID 100

// 创建消息队列
int main()
{
    key_t key;
    int msgid;

    // 函数ftok把一个已存在的路径名和一个整数标识符转换成一个key_t值，称为IPC键值（也称IPC key键值）
    key = ftok(PATHNAME, PRO_ID);
    if (key == -1)
    {
        perror("ftok(): ");
        exit(EXIT_FAILURE);
    }

    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1)
    {
        perror("msgget(): ");
        exit(EXIT_FAILURE);
    }

    printf("msg id: %d\n", msgid);

    return 0;
}
