#include <stdio.h>

enum Day 
{
    MON = 1,
    TUE,
    WED,
    THU,
    FRI,
    SAT,
    SUM
};

int main(int argc, char const *argv[])
{
    enum Day today = THU;

    // GCC对枚举类型进行了扩展，可以使用非enum中的任何之。
    today = 8;
    printf("today = %d\n", today);


    int date = 0;
    printf("please input you want check date: ");
    scanf("%d", &date);

    switch (date)
    {
        case MON:
            printf("today is MON\n");
            break;
        case TUE:
            printf("today is TUE\n");
            break;
        case WED:
            printf("today is WED\n");
            break;
    
    }

    return 0;
}
