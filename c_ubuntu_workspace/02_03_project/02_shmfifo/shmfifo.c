#include "shmfifo.h"

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