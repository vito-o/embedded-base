#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define PATHNAME "."
#define PRO_ID 100

#define SZ 256

int main(int argc, char const *argv[])
{
    key_t key;
    int shmid, ret, i;
    char buffer[10] = {0};
    void *addr = NULL;

    key = ftok(PATHNAME, PRO_ID);
    if (key == -1)
    {
        perror("[ERROR] key(): ");
        exit(EXIT_FAILURE);
    }

    // 创建共享内存
    shmid = shmget(key, SZ, IPC_CREAT|0644);
    if (shmid == -1)
    {
        perror("shmget(): ");
        exit(EXIT_FAILURE);
    }

    printf("shmid = %d\n", shmid);

    // 将共享内存映射到进程的地址空间中
    addr = shmat(shmid, NULL, 0);
    if (addr == (void *)-1)
    {
        perror("[ERROR] shmat(): ");
        return -1;
    }

    // 将共享内存中的数据拷贝到数组
    memcpy(buffer, addr, 10);

    printf("buffer: %s\n", buffer);

    shmdt(addr);

    return 0;
}
