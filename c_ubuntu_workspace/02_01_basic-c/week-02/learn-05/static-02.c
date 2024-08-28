#include <stdio.h>

extern int global_var;

void fun()
{
    printf("global_var = %d\n", global_var);
}

int main(int argc, char const *argv[])
{
    
    fun();

    return 0;
}
