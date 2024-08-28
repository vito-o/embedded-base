#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

sem_t unnamed_sem;

int shard_num = 0;

void *plusOne(void *argv) 
{
    sem_wait(&unnamed_sem);
    int tmp = shard_num + 1;
    shard_num = tmp;
    sem_post(&unnamed_sem);
}

int main() 
{
    /*
        提前初始化信号量

        sem_t *__sem： 填写信号量的地址
        int __pshared： 使用方式 0表示线程间使用 1表示进程间通信
        unsigned int __value： 初始值
        return: 成功返回0 失败返回-1
        int sem_init (sem_t *__sem, int __pshared, unsigned int __value)
    */
    int sem_r = sem_init(&unnamed_sem, 0, 1);
    if (sem_r != 0)
    {
        perror("sem_init");
    }

    pthread_t tid[10000];
    for (int i = 0; i < 10000; i++) {
        pthread_create(tid + i, NULL, plusOne, NULL);
    }

    for (int i = 0; i < 10000; i++) {
        pthread_join(tid[i], NULL);
    }
    
    printf("shard_num is %d\n", shard_num);

    int des_r = sem_destroy(&unnamed_sem);
    if (des_r != 0)
    {
        perror("sem_destroy");
    }

    return 0;
}