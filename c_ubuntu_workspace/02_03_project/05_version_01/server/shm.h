#ifndef __SHM_H__
#define __SHM_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

enum shm_creat_status {
    SHM_HAS_EXIST = 0,
    SHM_CREAT_NEW,
    SHM_CREAT_ERROR
};

/* 创建共享内存 */
extern enum shm_creat_status shm_create(size_t size, int *pshmid);

/* 将创建好的共享内存连接到某个进程，并指定内存空间 */
extern void *shm_at(int shmid);

/* 脱钩函数，把共享内存与当前进程脱离开 */
extern int shm_dt(const void *shmaddr);

/* 删除共享内存 */
extern int shm_del(int shmid);

#endif