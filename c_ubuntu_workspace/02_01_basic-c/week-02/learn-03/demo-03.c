#include <stdio.h>
#include <string.h>
// 声明匿名结构体的同时定义变量并初始化

// 结构体类型，声明为全局
struct
{
    char name[20];
    int id;
    int score;
} st = {"rose", 2, 100};

int main(int argc, char const *argv[])
{
   
    printf("NAME\tID\tSCORE\n");
    printf("%s\t%d\t%d\n", st.name, st.id, st.score);

    return 0;
}
