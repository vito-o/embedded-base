#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    FILE *fp = NULL;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <pathname> \n", argv[0]);
        return -1;
    }

    fp = fopen(argv[1], "w+");  // w+: 可读写，文件不存在就创建，否则清零
    if (fp == NULL)
    {
        perror("Error fopen(): ");
        return -1;
    }
    
    fclose(fp);

    return 0;
}
