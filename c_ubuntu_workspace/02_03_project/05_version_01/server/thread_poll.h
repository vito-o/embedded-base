#ifndef __THREAD_H__
#define __THREAD_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>

typedef struct tpool_task {
    void (*function) (void *arg);
    void *arg;
} tpool_task_t;

typedef struct tpoll {
    tpool_task_t *tp_task;

    int tp_qcapacity;   // 任务队列容量
    int tp_qsize;       // 任务队列长度

    int tp_qfront;      // 队头
    int tp_qrear;       // 队尾
    pthread_t *tp_work_thread_ids;  // 指向存储线程id空间的指针

    int tp_number_of_threads;    // 总的线程数量

    pthread_mutex_t tp_mutex_pool;  // 线程池互斥锁

    pthread_cond_t tp_cond_empty;
    pthread_cond_t tp_cond_full;

    bool tp_shutdown;
} tpool_t;

/* 
    线程池初始化 
    cnt: 线程池里线程的数量
    queuesize: 任务队列里最多可以装多少个任务
*/
extern tpool_t *thread_pool_init(int cnt, int queuesize);

/* 线程池添加任务 */
extern void thread_pool_add_task(tpool_t *pool, void (*task)(void *arg), void *arg);

/* 线程池销毁 */
extern int thread_pool_destroy(tpool_t *pool);

/* 线程执行函数 */
void *tp_worker(void *arg);

#endif