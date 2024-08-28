#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;

// 初始化锁
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// 初始化条件变量
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *producer(void *argv) 
{
    int item = 1;
    while(1)
    {
        // 获取互斥锁，拿不到等
        pthread_mutex_lock(&mutex);

        // 如果缓冲区满了，先让出，等消费者读取
        while (count == BUFFER_SIZE)
        {
            // 暂停线程，等待唤醒
            pthread_cond_wait(&cond, &mutex);
        }

        // 能到这里说明缓冲区没满，可以写一个
        buffer[count++] = item++;
        printf("by发送了一个幸运数字%d\n", buffer[count-1]);

        // 通知消费者可以消费数据了
        pthread_cond_signal(&cond);

        // 释放互斥锁
        pthread_mutex_unlock(&mutex);
    }
}

void *consumer(void *argv) 
{
    while (1)
    {
        // 获取互斥锁，拿不到就等
        pthread_mutex_lock(&mutex);

        // 如果缓冲区为空，则等待生产者生产数据
        while (count == 0)
        {
            // 暂停线程，等待唤醒
            pthread_cond_wait(&cond, &mutex);
        }
        
        // 消费数据
        printf("我收到了幸运数字%d\n", buffer[--count]);

        // 通知生产者可以生产数据了
        pthread_cond_signal(&cond);

        // 释放互斥锁
        pthread_mutex_unlock(&mutex);
    }
    
}

int main(int argc, char const *argv[])
{
    pthread_t producer_thread, consumer_thread;

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}
