#include <stdio.h>
//联合体
//联合体是为了节省内存用的，比如下面的stu中每次使用的时候 必须只使用a\b\c中的一个，就以这三个中的最大某一个的长度作为stu的长度，

union stu
{
    char a;
    int b;
    short c;
};

struct student
{
    char a;
    int b;
    short c;
};

int main(int argc, char const *argv[])
{
    struct student st;
    union stu su;

    printf("sizeof(struct): %d\n", sizeof(st)); //12
    printf("sizeof(union): %d\n", sizeof(su));  //4

    return 0;
}
