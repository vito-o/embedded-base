#include <stdio.h>
#include <stdlib.h>

// 读写二进制文件，如图片视频等等
int main(int argc, char const *argv[])
{
    FILE *fp = NULL;
    float numbers[5] = {1.1, 1.2, 1.3, 1.4, 1.5};
    float result[5] = {0};

    size_t witems = 0;
    size_t ritems = 0;
    
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <pathname> \n", argv[0]);
        return -1;
    }

    fp = fopen(argv[1], "w+");  //
    if (fp == NULL)
    {
        perror("Error fopen(): ");
        return -1;
    }
    
    witems = fwrite(numbers, sizeof(float), 5, fp);
    if (witems != 5)
    {
        perror("Error fwrite(): ");
        return -1;
    }
    
    // 將文件的偏移設置位0(从头开始)
    fseek(fp, 0, SEEK_SET);

    ritems = fread(result, sizeof(float), 5, fp);
    if (ritems != 5)
    {
        perror("Error ritems(): ");
        return -1;
    }
    
    int i = 0;
    for (i = 0; i < 5; i++)
    {
        printf("%f ", result[i]);
    }
    printf("\n");

    fclose(fp);

    return 0;
}

