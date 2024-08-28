#include <stdio.h>

// 位域

// 空域
/**
 * struct info 
 * {
 *      unsigned char a:4;
 *      unsigned char :4;  // 空域
 *      unsigned char b:4; // 从下一单元开始存放
 *      unsigned char c:4;
 * };
 * 
 * a a a a | | | |         // 这里的|就是空域，空的目的是让b从下一个单元（字节）开始存放
 * b b b b c c c c         // 空域只是填充不能使用
 * 
 */


typedef struct bs
{
    unsigned int a:1;
    unsigned int b:3;
    unsigned int c:4;
} bit_t;


int main(int argc, char const *argv[])
{
    bit_t bit;
    bit_t *pbit;

    bit.a = 1;
    bit.b = 7;
    bit.c = 15;
    printf("%d,%d,%d\n",bit.a, bit.b, bit.c);

    pbit = &bit;
    pbit->a = 0;
    pbit->b &= 3;
    pbit->c != 1;
    printf("%d,%d,%d\n",bit.a, bit.b, bit.c);

    return 0;
}
