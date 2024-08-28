#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h> 

// 定义结果结构体
typedef struct Result
{
    char *p;
    int len;
} Result;

// red
void *red_thread(void *argv)
{
    Result *result = malloc(sizeof(Result));
    char code = *(char *)argv;
    // 存放回信
    char *ans = malloc(101);
    while (1)
    {
        fgets(ans, 100, stdin);
        if (ans[0] == code)
        {
            // 接收到对应的消息
            free(ans);
            printf("red 离开了\n");
            char *redAns = strdup("red独自去了纽约\n");
            result->p = redAns;
            result->len = strlen(redAns);
            // 线程结束，输出返回值
            pthread_exit((void *)result);
        }
        else
        {
            printf("red还在等你\n");
        }
    }
}

// white
void *white_thread(void *argv)
{
    Result *result = malloc(sizeof(Result));
    char code = *(char *)argv;
    // 存放回信
    char *ans = malloc(101);
    while (1)
    {
        fgets(ans, 100, stdin);
        if (ans[0] == code)
        {
            // 接收到对应的消息
            free(ans);
            printf("white 离开了\n");
            char *whiteAns = strdup("white独自去了巴黎\n");
            result->p = whiteAns;
            result->len = strlen(whiteAns);
            // 线程结束，输出返回值
            pthread_exit((void *)result);
        }
        else
        {
            printf("white还在等你\n");
        }
    }
}

int main(int argc, char const *argv[])
{
    pthread_t pid_red;
    pthread_t pid_white;

    char red_code = 'r';
    char white_code = 'w';

    Result *red_result = NULL;
    Result *white_result = NULL;

    // 创建线程
    // 创建红玫瑰线程
    pthread_create(&pid_red, NULL, red_thread, &red_code);
    // 创建白玫瑰线程
    pthread_create(&pid_white, NULL, white_thread, &white_code);

    // 获取red结果
    pthread_join(pid_red, (void **)&red_result);
    printf("red故事结局: %s\n", red_result->p);
    // 释放内存
    free(red_result->p);
    free(red_result);


    // 获取red结果
    pthread_join(pid_white, (void **)&white_result);
    printf("red故事结局: %s\n", white_result->p);
    // 释放内存
    free(white_result->p);
    free(white_result);

    return 0;
}
