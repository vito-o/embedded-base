#include <stdio.h>

// 位域

typedef struct
{
    //int类型占4个字节，但这里中的位于声明age只需要3个二进制位，所以如果可以，这里的age只需要一个字节（八位）就可以存储
    // unsigned int age:3;
    unsigned char age:3;
} s_t;


int main(int argc, char const *argv[])
{
    s_t t;
    t.age = 4;   
    printf("sizeof(t): %d\n", sizeof(t));  //4

    return 0;
}
