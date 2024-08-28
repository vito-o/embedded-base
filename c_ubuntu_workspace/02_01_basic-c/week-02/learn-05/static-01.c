#include <stdio.h>

void fun1()
{
    static int a;
    printf("a = %d\n", a);
}

void fun2()
{
    static int b = 10;
    b++;
    printf("b = %d\n", b);
}

int main(int argc, char const *argv[])
{
    fun1();
    printf("-=-------------------------\n");
    fun2();
    fun2();
    fun2();

    return 0;
}
