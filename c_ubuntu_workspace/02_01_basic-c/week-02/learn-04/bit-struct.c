#include <stdio.h>

// 位域

struct
{
    unsigned int width;
    unsigned int height;
} status1;

// width:1指的是占一个二进制位
struct
{
    unsigned int width:1;
    unsigned int height:1;
} status2;

int main(int argc, char const *argv[])
{
    
    printf("sizeof(status1): %ld\n", sizeof(status1));  //8
    printf("sizeof(status2): %ld\n", sizeof(status2));  //4
    return 0;
}
