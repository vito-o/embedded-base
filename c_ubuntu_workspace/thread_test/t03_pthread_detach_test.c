#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void *task(void *argv)
{
    printf("Thread started\n");
    sleep(2);
    printf("Thread finished\n");
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t tid;

    // 创建线程
    pthread_create(&tid, NULL, task, NULL);

    // 使用pthread_detach 让线程自动回收资源（不等待）
    pthread_detach(tid);

    // 主线程继续工作
    printf("Main thread continues\n");

    sleep(3);
    
    printf("Main thread ending\n");

    return 0;
}
