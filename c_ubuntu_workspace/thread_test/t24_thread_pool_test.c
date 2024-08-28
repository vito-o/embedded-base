#include <glib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// 人物函数
void task_func(gpointer data, gpointer user_data)
{
    int task_num = *(int *) data;
    free(data);
    printf("Executing task is %d... \n", task_num);
    sleep(1);
    printf("Task %d completed\n", task_num);
}

int main(int argc, char const *argv[])
{
    // 创建线城池
    GThreadPool *thread_pool = g_thread_pool_new(task_func, NULL, 5, TRUE, NULL);

    // 向线程池添加任务
    for (int i = 0; i < 10; i++)
    {
        int *tmp = malloc(sizeof(int));
        *tmp = i + 1;
        g_thread_pool_push(thread_pool, tmp, NULL);
    }

    // 等待所有任务完成
    g_thread_pool_free(thread_pool, FALSE, TRUE);

    printf("All tasks completed\n");

    return 0;
}
