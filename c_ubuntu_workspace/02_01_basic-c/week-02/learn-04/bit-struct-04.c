#include <stdio.h>

// 位域

//------------------------------------------------------
//相邻两个位域字段的类型相同，且其位宽之和小于或等于其类型的sizeof大小，则后面的位于字段将相邻前一个字段存储，直到不能容纳为止；
struct Bit1
{
    unsigned char a:1;
    unsigned char b:3;
    unsigned char c:4;
} t1;
//------------------------------------------------------
//如果相邻的两个位域字段的类型相同，且其位宽之和大于其类型的sizeof大小，则较大的位域字段将从下一个存储大院的起始地址处开始存放，
//其偏移量恰好位其类型的sizeof大小的整数倍
// a a | | | | | |
// b b b b b b b |
// c c c c | | | |
struct Bit2
{
    unsigned char a:2;
    unsigned char b:7;  //2 + 7 > 8, 2bytes存储, b回到下一个字节开始存储
    unsigned char c:4;  //大于sizeof(char)
} t2;
//------------------------------------------------------
//gcc下采取压缩的方式，3个成员挨着存储
// a a a a a a a a
// a a | | | | | |
// b b b b | | | |
// c c c c | | | |
struct Bit3
{
    unsigned int a:12;
    unsigned char b:4;
    unsigned int c:4;
} t3;
//------------------------------------------------------
//如果位域字段之间穿插着非位域字段，则不进行压缩
struct Bit4
{
    unsigned int a:12;
    unsigned int b;
    unsigned int c:4;
} t4;
//------------------------------------------------------
int main(int argc, char const *argv[])
{
    printf("sizeof(t1) = %d\n", sizeof(t1));    //sizeof(t1) = 1
    printf("sizeof(t2) = %d\n", sizeof(t2));    //sizeof(t2) = 3
    printf("sizeof(t3) = %d\n", sizeof(t3));    //sizeof(t3) = 4
    printf("sizeof(t4) = %d\n", sizeof(t4));    //sizeof(t4) = 12

    return 0;
}

// 位域一般不用指针，没啥意义