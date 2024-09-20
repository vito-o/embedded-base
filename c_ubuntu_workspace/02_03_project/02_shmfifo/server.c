#include <stdio.h>
#include <string.h>
#include "shm.h"

#define SHM_SZ 256

int main()
{
    int shmid;
    void *addr = NULL;
    char buffer[16] = {0};

    enum shm_creat_status shm_status;

    shm_status = shm_create(SHM_SZ, &shmid);
    if (shm_status == SHM_CREAT_NEW)
        printf("shared memory creat new.\n");
    else
        printf("shared memory has exist.\n");

    addr = shm_at(shmid);

    // 将共享内存的数据拷贝到buffer中
    memcpy(buffer, addr, 10);
    printf("buffer: %s\n", buffer);

    shm_dt(addr);
    shm_del(shmid);

    return 0;
}
