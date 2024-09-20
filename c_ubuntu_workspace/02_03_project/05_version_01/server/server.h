#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

enum work_mode {
    PUBLISH = 0,    // 发布消息
    SUBSCRIBE,      // 订阅消息
};

#define TOPIC_SZ 64
#define CONTENT_SZ 64

typedef struct packet {
    char topic[TOPIC_SZ];
    pid_t pid;
    enum work_mode mode;
    char content[CONTENT_SZ];
} packet_t;

extern void server_init();
extern void runloop();

extern void do_subscribe(char *topic, pid_t pid);
extern void do_publish(char *topic, char *content);

#endif