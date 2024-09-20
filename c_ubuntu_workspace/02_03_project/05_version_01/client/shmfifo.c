#include "shmfifo.h"
#include <string.h>

static int g_shmid;

/* 创建环形队列，初始化 */
shm_fifo_t *shmfifo_init(int blocks, int blksz)
{
    int shm_sz = 0;
    enum shm_creat_status s_creat_status;
    unsigned short values[] = {0, blocks, 1};

    shm_fifo_t *p_shm_fifo = malloc(sizeof(shm_fifo_t));
    if (!p_shm_fifo)
        return NULL;
    
    shm_sz = blocks * blksz + sizeof(shm_head_t);

    s_creat_status = shm_create(shm_sz, &g_shmid);
    if (s_creat_status != SHM_CREAT_ERROR)
    {
        p_shm_fifo->p_head = (shm_head_t *) shm_at(g_shmid);
        if (s_creat_status == SHM_CREAT_NEW)
        {
            p_shm_fifo->p_head->rpos = 0;
            p_shm_fifo->p_head->wpos = 0;
            p_shm_fifo->p_head->blocks = blocks;
            p_shm_fifo->p_head->blksz = blksz;
            p_shm_fifo->p_head->semid = sem_create(3, values);
        }
        p_shm_fifo->p_payload = (char *) (p_shm_fifo->p_head + 1);
        return p_shm_fifo;
    }
    return NULL;
}

/* 销毁环形队列 */
void shmfifo_destroy(shm_fifo_t *fifo)
{
    // 删除信号量集合
    sem_del(fifo->p_head->semid);
    // 把共享内存与当前进程脱离开
    shm_dt(fifo->p_head);
    // 删除共享内存
    shm_del(g_shmid);
    // 释放动态分配的内存
    free(fifo);
}

/* 给环形队列发送消息 */
void shmfifo_put(shm_fifo_t *fifo, const void *buf)
{
    // SEM_FULL_ID：是对多个消息发送者，并发发送消息时，只有一个进程获取该信号量，可以往下执行，其他阻塞等待
    int pos = 0;

    // sem_p 占用信号量（信号量减1），占用不了时阻塞。
    sem_p(fifo->p_head->semid, SEM_FULL_ID);    //占用判满的信号量
    sem_p(fifo->p_head->semid, SEM_MUTEX_ID);

    // 计算偏移量
    pos = fifo->p_head->wpos * fifo->p_head->blksz;

    // 拷贝数据到环形队列
    memcpy(fifo->p_payload + pos, buf, fifo->p_head->blksz);

    // 更新偏移
    fifo->p_head->wpos = (fifo->p_head->wpos + 1) % (fifo->p_head->blocks);
    
    // sem_v 释放信号量（信号量加1）
    sem_v(fifo->p_head->semid, SEM_MUTEX_ID);
    // SEM_EMPTY_ID，这里释放该信号，是为了通知，让正在阻塞的要获取消息的进程，可以不阻塞了
    sem_v(fifo->p_head->semid, SEM_EMPTY_ID);
}

/* 从环形队列获取消息 */
void shmfifo_get(shm_fifo_t *fifo, void *buf)
{
    int pos = 0;

    //占用盘空信号量
    sem_p(fifo->p_head->semid, SEM_EMPTY_ID);
    sem_p(fifo->p_head->semid, SEM_MUTEX_ID);

    // 计算偏移量
    pos = fifo->p_head->rpos * fifo->p_head->blksz;

    // 从环形队列中拷贝数据
    memcpy(buf, fifo->p_payload + pos, fifo->p_head->blksz);

    // 更新偏移
    fifo->p_head->rpos = (fifo->p_head->rpos +1) % (fifo->p_head->blocks);

    sem_v(fifo->p_head->semid, SEM_MUTEX_ID);
    sem_v(fifo->p_head->semid, SEM_FULL_ID);
}