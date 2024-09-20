#include "server.h"
#include "shmfifo.h"
#include "thread_poll.h"
#include "hashmap.h"
#include "msg.h"

#define DEBUG
#define BLOCK_CNT 10
#define THREAD_CNT 10
#define TASK_CNT 10
#define RESULT_SZ 5

static shm_fifo_t *g_shmfifo = NULL;
static tpool_t *g_tpool = NULL;
static hashtable_t **g_hashtable = NULL;
static int g_msgid = 0;

void server_init()
{
    // 创建环形队列，接收消息
    g_shmfifo = shmfifo_init(BLOCK_CNT, sizeof(packet_t));
    // 初始化线程池，通过线程池中的线程执行接收到的消息
    g_tpool = thread_pool_init(THREAD_CNT, TASK_CNT);
    // 创建hash表，可以记录哪个进程id 订阅了哪些主题
    g_hashtable = create_hashtable();
    // 创建消息队列，服务端发送的消息，客户端可以读取
    g_msgid = msg_create();
}

void task_handler(void *arg)
{
    packet_t *packet = (packet_t *)arg;

    // 发布模式
    if (packet->mode == PUBLISH)
    {
        printf("publicsh.\n");
        do_publish(packet->topic, packet->content);
    }
    // 订阅模式
    else if (packet->mode == SUBSCRIBE)
    {
        printf("subscribe.\n");
        do_subscribe(packet->topic, packet->pid);
    }
}


void runloop()
{
    packet_t *packet = NULL;

    for(;;)
    {
        packet = (packet_t *)malloc(sizeof(packet_t));
        memset(packet, 0, sizeof(packet_t));
        // 消费循环队列中的消息，没有消息时进行阻塞等待
        shmfifo_get(g_shmfifo, (void *)packet);
        // 将任务发送到线程池中的线程去执行
        thread_pool_add_task(g_tpool, task_handler, (void *)packet);

#ifdef DEBUG
    printf("topic: %s, pid: %d, mode: %d, content: %s\n",
        packet->topic,
        packet->pid,
        packet->mode,
        packet->content);
#endif

    }
}

void do_subscribe(char *topic, pid_t pid)
{
    datatype_t value;
    strcpy(value.topic, topic);
    value.pid = pid;

    insert_data_hash(g_hashtable, topic, value);

#ifdef DEBUG
    printf_hash_table(g_hashtable);
#endif
}

void do_publish(char *topic, char *content)
{
    pid_t result[RESULT_SZ];
    int ret;
#ifdef DEBUG
    printf("do publish.\n");
#endif

    // hashmap查询所有订阅进程pid
    ret = search_hash_table(g_hashtable, topic, result);
    if (ret != 0)
    {
#ifdef DEBUG
    printf("ret = %d\n", ret);
#endif  
        for (int i = 0; i < ret; i++)
        {   // 给订阅的每个进程id发送当前消息
            ret = msg_send(g_msgid, result[i], content);
            printf("~~ ret = %d\n", ret);
        }
    }
}