#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *do_thread(void *arg)
{
    printf("Thread start. arg = %d\n", *(int *)arg);

    pthread_exit(NULL); //线程的退出
}

int main()
{
    int err;
    pthread_t tid = 0;
    int num = 100;

    err = pthread_create(&tid, NULL, do_thread, &num);
    if (err != 0)
    {
        fprintf(stderr, "[ERROR] pthread_create: < %s >\n", strerror(err));
        exit(EXIT_FAILURE);
    }

    // 等待指定线程结束，
    pthread_join(tid, NULL);

    printf(" tid = %ld\n ", tid);

    return 0;
}
