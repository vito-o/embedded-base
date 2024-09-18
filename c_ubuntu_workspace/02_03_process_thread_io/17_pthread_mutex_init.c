#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
// 动态创建互斥锁
static int global = 0;

pthread_mutex_t mutex;

void *do_thread(void *arg)
{
    int loops = *(int *) arg;
    int i, tmp = 0;

    for (i = 0; i < loops; i++)
    {   
        pthread_mutex_lock(&mutex);
        tmp = global;
        tmp++;
        global = tmp;
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char const *argv[])
{
    int err, i = 0;
    pthread_t tid[2] = {0};
    int loops = 0;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: < %s > < count loops >\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pthread_mutex_init(&mutex, NULL);

    loops = atoi(argv[1]);

    for (i = 0; i < 2; i++)
    {
        err = pthread_create(&tid[i], NULL, do_thread, &loops);
        if (err != 0)
        {
            fprintf(stderr, "[ERROR] pthread_create(): < %s > \n", strerror(err));
            exit(EXIT_FAILURE);
        }
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    
    pthread_mutex_destroy(&mutex);
    
    printf("global = %d\n", global);

    return 0;
}
