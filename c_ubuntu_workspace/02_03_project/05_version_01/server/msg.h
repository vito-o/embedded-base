#ifndef __MSG_H__
#define __MSG_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

/* 创建消息队列 */
extern int msg_create();

/* 消息发送 */
extern int msg_send(int msgid, long mtype, char *buf);

/* 消息接收 */
extern int msg_recv(int msgid, long mtype, char *buf, int len);

/* 消息队列删除 */
extern int msg_del(int msgid);

#endif