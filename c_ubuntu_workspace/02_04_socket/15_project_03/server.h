#ifndef __SERVER_H__
#define __SERVER_H__

#include "global.h"

#define STD_HEADER "Connection: close\r\n"                                                                        \
                   "Server: MJPG-Streamer/0.2\r\n"                                                                \
                   "Cache-Control: no-store, no-cache, must-revalidate, pre-check=0, post-check=0, max-age=0\r\n" \
                   "Pragma: no-cache\r\n"                                                                         \
                   "Expires: Mon, 3 Jan 2013 12:34:56 GMT\r\n"

#define BOUNDARY "cyg-boundary"
#define WEB_DIR "www"

typedef enum {
    A_SNAPSHOT,
    A_STREAM,
    A_FILE
} answer_t;

typedef struct {
    answer_t type;
    char *parm;
} request_t;

extern int init_tcp(const char *ipstr, unsigned short port, int backlog);

extern void *client_thread(void *arg);

extern int analyse_http_request(const char *buf, request_t *req);
extern void send_file(int sockfd, char *pathfile);
extern void send_snapshot(int sockfd);
extern void send_stream(int sockfd);

#endif