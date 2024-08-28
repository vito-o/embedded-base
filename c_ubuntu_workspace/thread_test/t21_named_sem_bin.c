#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
// 有名信号量用作二进制信号量

int main(int argc, char const *argv[])
{
    char *sem_name = "/named_sem";
    // 初始化有名信号量
    sem_t *sem = sem_open(sem_name, O_CREAT, 0666, 1);


    char *shm_name = "/named_sem_shm";

    // 初始化内存共享对象
    int fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    // 调整内存共享对象的大小
    ftruncate(fd, sizeof(int));
    // 将内存共享对象映射到内存空间
    int *value = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    // 初始化共享变量指针指向位置的值
    *value = 0;

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
    }


    sem_wait(sem);
    int tmp = *value + 1;
    sleep(1);
    *value = tmp;
    sem_post(sem);



    // 每个进程都英国在使用完毕后关闭对信号量的连接
    sem_close(sem);

    if (pid > 0)
    {
        waitpid(pid, NULL, 0);
        printf("子进程执行结束， value = %d\n", *value);

        // 有名信号量的取消链接只能执行一次
        sem_unlink(sem_name);
    }

    // 父子进程都解除内存共享对象的映射，并关闭相应的文件描述符
    munmap(value, sizeof(int));
    close(fd);

    // 只有父进程应该释放共享内存
    if (pid > 0)
    {
        if (shm_unlink(shm_name) == -1)
        {
            perror("shm_unlink");
        }
    }

    return 0;
}
