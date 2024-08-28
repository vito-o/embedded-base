#include <stdio.h>
#include <string.h>
// 声明结构体后定义变量

// 结构体类型，声明为全局
struct student
{
    char name[20];
    int id;
    int score;
};

int main(int argc, char const *argv[])
{
    // int a;
    // int a[5];
    struct student st;
    // struct student st[5]
    struct student *sp = &st;   //&st == 0x8000 == sp

    // st.name = "jack"; //error   st.name char name[20]为字符串 为常量不能直接赋值，需要用strcpy
    strcpy(st.name, "jack");
    (&st)->score = 100; // sp->score == 0x8000->score  类似

    printf("NAME\tID\tSCORE\n");
    printf("%s\t%d\t%d\n", st.name, st.id, st.score);

    return 0;
}
