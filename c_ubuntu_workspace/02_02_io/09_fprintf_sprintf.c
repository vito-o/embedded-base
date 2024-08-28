#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    FILE *fp = NULL;

    int numa = 10;
    int numb = 20;
    int numc = 30;
    char buffer[64] = {0};

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
    
    fprintf(fp, "%d-%d-%d", numa, numb, numc); //将三个整数按照特定的格式写入文件中

    sprintf(buffer, "%d-%d-%d", numa, numb, numc); //将三个整数按照特定的格式写入字符从缓冲区中
    printf("buffer : %s\n", buffer);

    fclose(fp);

    return 0;
}

