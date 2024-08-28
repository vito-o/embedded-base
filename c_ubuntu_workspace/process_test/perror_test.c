#include <stdio.h>

int main(int argc, char const *argv[])
{
    fopen("bucunzai.txt", "r");
    perror("open");
    return 0;
}
