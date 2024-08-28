#include <stdio.h>
//条件编译
/*
#ifndef 宏名 判断宏名是否没有定义
    c语言豫剧
#endif
功能：若没有定义，会执行对应的c语言语句，若是定义了则不会执行
 */

// #define DEBUG

int main(int argc, char const *argv[])
{
    int a[5] = {10,20,30,40,50};
    int i = 0;
    int *p= a;

#ifndef DEBUG
    printf("first...\n");
    for(i = 0; i < 5; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
#else   //等价于注释
    printf("second...\n");
    for(i = 0; i < 5; i++)
    {
        printf("p = %d ", p[i]);
    }
    printf("\n");
#endif
    /* code */
    return 0;
}
