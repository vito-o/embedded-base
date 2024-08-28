#include <stdio.h>
//条件编译
int main(int argc, char const *argv[])
{
    int a[5] = {10,20,30,40,50};
    int i = 0;
    int *p= a;

#if 0
    for(i = 0; i < 5; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
#else   //等价于注释
    for(i = 0; i < 5; i++)
    {
        printf("p = %d ", p[i]);
    }
    printf("\n");
#endif
    /* code */
    return 0;
}
