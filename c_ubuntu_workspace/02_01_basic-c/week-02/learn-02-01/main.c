#include <stdio.h>

extern int global;  //全局变量的声明
extern void fun();  //全局函数的声明

int main(int argc, char const *argv[])
{
    printf("global = %d\n", global);
    fun();
    /* code */
    return 0;
}
