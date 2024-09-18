#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *do_thread1(void *arg)
{
    printf("Thread start.\n");

    pthread_exit(NULL); //线程的退出
}

void *do_thread2(void *arg)
{
    printf("Thread start.\n");

    pthread_exit(NULL); //线程的退出
}

int main()
{
    int err;
    pthread_t tid1 = 0;
    pthread_t tid2 = 0;

    err = pthread_create(&tid1, NULL, do_thread1, NULL);
    if (err != 0)
    {
        fprintf(stderr, "[ERROR] pthread_create: < %s >\n", strerror(err));
        exit(EXIT_FAILURE);
    }

    err = pthread_create(&tid2, NULL, do_thread2, NULL);
    if (err != 0)
    {
        fprintf(stderr, "[ERROR] pthread_create: < %s >\n", strerror(err));
        exit(EXIT_FAILURE);
    }

    // 等待指定线程结束，
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf(" tid1 = %ld\n ", tid1);
    printf(" tid2 = %ld\n ", tid2);

    return 0;
}
