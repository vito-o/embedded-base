#include <stdio.h>
#include <string.h>
// 结构体的大小

struct student
{
    char name[5];
    int id;
    short score;
};

void output_student(struct student *sp)
{
    printf("sizeof sp is %d\n", sizeof(sp));
    printf("NAME\tID\tSCORE\n");
    printf("%s\t%d\t%d\n", sp->name, sp->id, sp->score);
}

int main(int argc, char const *argv[])
{
   struct  student st = {"jack", 1, 80};
   printf("sizeof st is %d\n", sizeof(st));
   
   output_student(&st);

    return 0;
}
