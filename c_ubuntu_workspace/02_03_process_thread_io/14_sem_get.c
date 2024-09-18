// 信号量是一种用于同步进程的机制，常用来解决资源共享冲突问题。
// 例如，当多个进程需要访问一个共享资源时，信号量可以确保每次只有一个进程能够访问该资源，从而防止竞争条件

// 信号量集合的创建与删除


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define SEM_PATHNAME "."
#define SEM_PRO_ID 100

union semun
{
    int val;
};

int main()
{
    int semid, ret;

    union semun s;

    // 通过 ftok 函数生成一个独特的键 key，用于标识这个信号量。ftok 结合文件路径和项目ID生成一个唯一的键，供信号量集使用。
    key_t key = ftok(SEM_PATHNAME, SEM_PRO_ID);
    if (key == -1)
    {
        perror("[ERROR] ftok() : ")	;
		return -1;
    }
    // 通过 semget 函数创建或获取一个信号量集，参数 1 表示创建一个包含一个信号量的集合。IPC_CREAT | 0666 表示创建一个新信号量集，
    // 如果信号量集不存在，并设置权限为所有用户可读写（0666）。
    semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1)
    {
        perror("[ERROR] semget() : ")	;
		return -1;
    }

    // 定义信号量初始值。这里将信号量的值设置为 1，表示资源是可用的。这是典型的二元信号量（binary semaphore），即用于进程间的互斥（mutex），类似于锁的作用。
    s.val = 1;

    // 使用 semctl 函数设置信号量集中的第一个信号量的初值为 1。这意味着该信号量的初始状态为“可用”，允许某个进程锁定该信号量。
    ret = semctl(semid, 0, SETVAL, s);
    if (ret == -1)
    {
        perror("[ERROR] semctl() : ");
        return -1;
    }

    return 0;
}


/*
ipcs -s

------ Semaphore Arrays --------
key        semid      owner      perms      nsems     
0x64038650 0          vito       666        1   

key：信号量的键值，ftok 生成的键。
semid：信号量集的 ID，用于标识该信号量集。
owner：信号量的所有者。
perms：信号量的权限。
nsems：信号量集中的信号量数量（在你的程序中是 1）。




在 C 语言中，0666 和 0x666 是不同的表示法，用来表达不同的数字体系。

0666：这是八进制表示法，表示八进制数 666，相当于十进制的 438。在权限的上下文中，八进制表示常用于定义文件或信号量的权限。具体权限表示如下：

0666 分解为 rw-rw-rw-，表示文件的所有者、所属组和其他用户都有读写权限（分别为读 4 和写 2 的和）。
0x666：这是十六进制表示法，表示十六进制数 666，相当于十进制的 1638，它与权限无关。在权限设置中，不常使用十六进制，因为 Unix 和 Linux 系统中的权限表示使用的是八进制数。

权限为什么用八进制？
权限通常以八进制表示，因为每个权限组（用户、组、其他）都有三个标志位：读、写、执行。这三个标志位可以用 3 位二进制数表示：

rwx = 111 = 7
rw- = 110 = 6
r-- = 100 = 4 因此，文件权限由 3 个这样的 3 位二进制数组成，总共是 9 位二进制数。这正好适合用八进制来简洁地表示。

*/