#include "sem.h"
#include <sys/sem.h>

#define SEM_PATHNAME "."
#define SEM_PRO_ID 99

union semun {
    int val;
    unsigned short *array;
};

/* 
    创建信号量集合 
    nsems: 信号量的个数
    values： 信号量值的数组
*/
int sem_create(int nsems, unsigned short values[])
{
    int semid, ret;
    key_t key;
    union semun s;

    key = ftok(SEM_PATHNAME, SEM_PRO_ID);
    if (key == -1)
    {
        perror("[ERROR] ftok(): ");
        return -1;
    }

    semid = semget(key, nsems, IPC_CREAT|0666);
    if (semid == -1)
    {
        perror("[ERROR] semget(): ");
        return -1;
    }

    s.array = values;

    ret = semctl(semid, 0, SETALL, s);
    if (ret == -1)
    {
        perror("[ERROR] semctl(): ");
        return -1;
    }

    return semid;
}

/* 
    占用资源 
    semid: 信号量集合的id
    semnum: 信号量的编号
*/
int sem_p(int semid, int semnum)
{
    struct sembuf sops;
    sops.sem_num = semnum;
    sops.sem_op = -1;           //-1: 占用资源
    sops.sem_flg = SEM_UNDO;    //进程终止，会自动释放信号量

    return semop(semid, &sops, 1);
}

/* 
    释放资源 
*/
int sem_v(int semid, int semnum)
{
    struct sembuf sops;
    sops.sem_num = semnum;
    sops.sem_op = 1;
    sops.sem_flg = SEM_UNDO;    //进程终止，会自动释放信号量

    return semop(semid, &sops, 1);
}

/* 
    删除信号量集合 
*/
int sem_del(int semid)
{
    return semctl(semid, 0, IPC_RMID, NULL);
}