#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *task(void *argv)
{
    printf("Thread started\n");

    // 禁止取消响应
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

    printf("Thread CancelState is disabled\n");

    // 设置取消类型为异步
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    // 模拟工作
    printf("Working...\n");
    sleep(1);
    printf("After Cancelled\n");
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t tid;
    void *res;    

    // 创建线程
    pthread_create(&tid, NULL, task, NULL);

    // 取消子进程
    if (pthread_cancel(tid) != 0)
    {
        perror("pthread_cancel");
    }

    // 等待子线程中止并获取其退出状态
    pthread_join(tid, &res);

    // 检查子线程是否被取消
    if (res == PTHREAD_CANCELED)
    {
        printf("Thread was canceled\n");
    }
    else
    {
        printf("Thread was not canceled, exit code: %ld\n", (long) res);
    }

    return 0;
}
