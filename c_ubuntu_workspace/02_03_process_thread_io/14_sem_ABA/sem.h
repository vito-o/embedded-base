#ifndef __SEM_H__
#define __SEM_H__

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

/* 创建信号量集合 */
extern int sem_create(int nsems, unsigned short values[]);

/* 占用资源 */
extern int sem_p(int semid, int semnum);

/* 释放资源 */
extern int sem_v(int semid, int semnum);

/* 删除信号量集合 */
extern int sem_del(int semid);

#endif