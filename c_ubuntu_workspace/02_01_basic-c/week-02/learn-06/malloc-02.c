#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5

int *get_memory_addr()
{
    int *addr = NULL;
    addr = (int *)malloc(sizeof(int) * N);

    if (NULL == addr)
    {
        printf("malloc is fail!\n");
    }

    memset(addr, 0, sizeof(int) * N);

    return addr;
}

//
void input_array(int *p)
{
    int i = 0;
    printf("please input %d data: ", N);
    for(i = 0; i < N; i++)
    {
        scanf("%d", &p[i]);
    }
}

void ouput_array(int *p)
{
    int i = 0;
    for(i = 0; i < N; i++)
    {
        printf("%d ", p[i]);
    }
    printf("\n");
}

//
int main(int argc, char const *argv[])
{
    int *t = NULL;

    t = get_memory_addr();

    input_array(t);
    ouput_array(t);

    free(t);
    t = NULL;

    /* code */
    return 0;
}
