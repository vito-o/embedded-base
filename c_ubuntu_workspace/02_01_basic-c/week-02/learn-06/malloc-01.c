#include <stdio.h>
#include <stdlib.h>

//
int main(int argc, char const *argv[])
{
    int *p = NULL;

    p = (int *)malloc(sizeof(int));
    if (NULL == p)
    {
        printf("malloc is fail\n");
        return -1;
    }

    memset(p, 0, sizeof(int));

    *p = 800;

    printf("*p = %d\n", *p);

    free(p);
    p = NULL;

    /* code */
    return 0;
}
