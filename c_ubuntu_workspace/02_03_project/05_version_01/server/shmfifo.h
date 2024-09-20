#include "sem.h"
#include "shm.h"

#define SEM_EMPTY_ID 0
#define SEM_FULL_ID 1
#define SEM_MUTEX_ID 2

typedef struct shm_head {
    int rpos;   //出队列的位置
    int wpos;   //入队列的位置

    int blocks; //数据块的数量
    int blksz;  //数据块的大小

    int semid;  //信号量集合的id
} shm_head_t;

typedef struct shm_fifo {
    shm_head_t *p_head;
    char *p_payload;
} shm_fifo_t;

/* 创建环形队列，初始化 */
extern shm_fifo_t *shmfifo_init(int blocks, int blksz);

/* 销毁环形队列 */
extern void shmfifo_destroy(shm_fifo_t *fifo);

/* 给环形队列发送消息 */
extern void shmfifo_put(shm_fifo_t *fifo, const void *buf);

/* 从环形队列获取消息 */
extern void shmfifo_get(shm_fifo_t *fifo, void *buf);