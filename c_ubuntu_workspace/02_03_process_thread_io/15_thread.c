#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *do_thread(void *arg)
{
    printf("Thread start.\n");

    pthread_exit(NULL); //线程的退出
}

int main()
{
    int err;
    pthread_t tid = 0;

    err = pthread_create(&tid, NULL, do_thread, NULL);
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
