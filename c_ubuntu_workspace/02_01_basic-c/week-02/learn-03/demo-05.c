#include <stdio.h>

typedef struct 
{
    char name[20];
    int id;
    int score;
} s_t;

void input_student(s_t *sp)
{
    printf("please input student[name id score]:");
    scanf("%s %d %d", sp->name, &(sp->id), &(sp->score));
}

void output_student(s_t *sp)
{
    printf("NAME\tID\tSCORE\n");
    printf("%s\t%d\t%d\n", sp->name, sp->id, sp->score);
}

int main(int argc, char const *argv[])
{
    s_t s1;

    input_student(&s1);
    output_student(&s1);

    return 0;
}
