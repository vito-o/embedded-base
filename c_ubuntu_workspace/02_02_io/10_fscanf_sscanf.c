#include <stdio.h>
#include <stdlib.h>
// 从文件中读取格式和数据并存储到指定变量中
int main(int argc, char const *argv[])
{
    FILE *fp = NULL;

    int numa = 10;
    int numb = 20;
    int numc = 30;
    char buffer[64] = "10-20-30";

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <pathname> \n", argv[0]);
        return -1;
    }

    fp = fopen(argv[1], "r");  //
    if (fp == NULL)
    {
        perror("Error fopen(): ");
        return -1;
    }
    
    fscanf(fp, "%d-%d-%d", &numa, &numb, &numc);
    printf("numa = %d; numb = %d; numc = %d\n", numa, numb, numc);

    numa = 0;
    numb = 0;
    numc = 0;

    sscanf(buffer, "%d-%d-%d", &numa, &numb, &numc);
    printf("numa = %d; numb = %d; numc = %d\n", numa, numb, numc);

    fclose(fp);

    return 0;
}

