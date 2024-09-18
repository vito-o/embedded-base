#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void *do_thread(void *arg)
{
    int i;
    for(i = 0; i < 5; i++)
    {
        printf("Thread start. i = %d\n", i);
        sleep(1);
    }
    pthread_exit(NULL); //线程的退出
}

int main()
{
    int i;
    int err;
    pthread_t tid[] = {0};

    for(i = 0; i < 5; i++)
    {
        err = pthread_create(&tid[i], NULL, do_thread, NULL);
        if (err != 0)
        {
            fprintf(stderr, "[ERROR] pthread_create: < %s >\n", strerror(err));
            exit(EXIT_FAILURE);
        }
        
        
    }

    for(i = 0; i < 5; i++)
    {
        // 等待指定线程结束，
        pthread_join(tid[i], NULL);
        printf("tid = %ld\n", tid[i]);
    }

    return 0;
}
