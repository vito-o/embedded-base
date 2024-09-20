#include <stdio.h>
#include <string.h>
#include "shm.h"

#define SHM_SZ 256

int main()
{
    int shmid;
    char buffer[10] = {0};
    void *addr = NULL;

    enum shm_creat_status shm_status;

    shm_status = shm_create(SHM_SZ, &shmid);
    if (shm_status == SHM_CREAT_NEW)
        printf("shared memory creat new.\n");
    else
        printf("shared memory has exist.\n");

    addr = shm_at(shmid);

    memset(addr, 'A', 10);

    shm_dt(addr);

    return 0;
}
