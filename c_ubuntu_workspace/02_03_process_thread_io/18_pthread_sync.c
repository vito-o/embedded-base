#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

static int number = 0;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
// 使用线程互斥锁和判断条件，实现线程同步（也就是指定现谁执行后谁执行）
void *thread_handler(void *arg)
{
    int cnt = atoi((char *) arg);
    int i, tmp;

    for (i = 0; i < cnt; i++)
    {
        pthread_mutex_lock(&mtx);
        printf("线程 [%ld] 生产一个产品，产品数量为：%d\n", pthread_self(), ++number);
        pthread_mutex_unlock(&mtx);
    }

    pthread_exit((void *) 0);
}

int main(int argc, char const *argv[])
{
    pthread_t tid;
    int i;
    int err;
    int total_of_produce = 0; //总的生产产品的数量
    int total_of_consume = 0; //总的消费产品的数量
    bool done = false;

    for (i = 0; i < argc; i++)
    {
        total_of_produce += atoi(argv[i]);
        err = pthread_create(&tid, NULL, thread_handler, (void *)argv[i]);
        if (err != 0)
        {
            perror("pthread_create(): ");
            exit(EXIT_FAILURE);
        }
    }

    for (;;)
    {
        pthread_mutex_lock(&mtx);
        while (number > 0)
        {
            total_of_consume++;
            printf("消费一个产品，产品数量为:%d\n", --number);
            done = total_of_consume >= total_of_produce;
            sleep(1);
        }
        pthread_mutex_unlock(&mtx);

        if (done)
            break;
        
    }

    return 0;
}
