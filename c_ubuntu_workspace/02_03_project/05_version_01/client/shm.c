#include "shm.h"

#define PATHNAME "../shm"
#define PRO_ID 101

enum shm_creat_status shm_create(size_t size, int *pshmid) 
{
    key_t key;
    int shmid;
    key = ftok(PATHNAME, size);

    // 获取共享内存的id(判断shmid是否存在)
    shmid = shmget(key, size, 0);
    // shmid不存在
    if (shmid == -1)
    {
        // • key: 这个共享内存段的名字，我们通常自定义数字并用key_t类型强转
        // • size: 需要共享的内存量
        // • shmflg:由九个权限标志构成，它们的用法和创建文件时使用的mode模式标志是一样的
        shmid = shmget(key, size, IPC_CREAT|0644);
        if (shmid == -1)
        {
            perror("[ERROR] shmget(): ");
            return SHM_CREAT_ERROR;
        }
        *pshmid = shmid;
        return SHM_CREAT_NEW;
    }
    else 
    {
        *pshmid = shmid;
        return SHM_HAS_EXIST;
    }

}

void *shm_at(int shmid)
{
    void *addr = NULL;
    // shmat：将创建好的共享内存连接到某个进程，并指定内存空间
    addr = shmat(shmid, NULL, 0);
    if (addr == (void *)-1)
    {
        perror("[ERROR] shmat(): ");
        return NULL;
    }
    return addr;
}

// shmdt：脱钩函数，把共享内存与当前进程脱离开
int shm_dt(const void *shmaddr)
{
    return shmdt(shmaddr);
}

int shm_del(int shmid)
{
    return shmctl(shmid, IPC_RMID, NULL);
}