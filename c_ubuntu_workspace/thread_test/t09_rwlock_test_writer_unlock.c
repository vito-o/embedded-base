#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_rwlock_t rwlock;
int shared_data = 0;

void *lock_read(void *argv)
{
    pthread_rwlock_rdlock(&rwlock);
    printf("this is %s, value is %d\n", (char *)argv, shared_data);
    pthread_rwlock_unlock(&rwlock);
}

void *lock_writer(void *argv)
{
    int tmp = shared_data + 1;
    sleep(1);
    shared_data = tmp;
    printf("this is %s, shared_data++\n", (char *)argv);
}

int main(int argc, char const *argv[])
{
    pthread_rwlock_init(&rwlock, NULL);

    pthread_t writer1, writer2;
    pthread_t read1, read2, read3, read4, read5, read6;

    pthread_create(&writer1, NULL, lock_writer, "writer1");
    pthread_create(&writer2, NULL, lock_writer, "writer2");

    sleep(3);
    
    pthread_create(&read1, NULL, lock_read, "read1");
    pthread_create(&read2, NULL, lock_read, "read2");
    pthread_create(&read3, NULL, lock_read, "read3");
    pthread_create(&read4, NULL, lock_read, "read4");
    pthread_create(&read5, NULL, lock_read, "read5");
    pthread_create(&read6, NULL, lock_read, "read6");

    pthread_join(writer1, NULL);
    pthread_join(writer2, NULL);
    pthread_join(read1, NULL);
    pthread_join(read2, NULL);
    pthread_join(read3, NULL);
    pthread_join(read4, NULL);
    pthread_join(read5, NULL);
    pthread_join(read6, NULL);

    pthread_rwlock_destroy(&rwlock);

    return 0;
}
