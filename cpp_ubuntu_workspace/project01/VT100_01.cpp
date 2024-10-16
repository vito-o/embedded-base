#include <iostream>

/*

\033[%d;%dH : 设置光标位置
\033[41;33m : 设置字体颜色和背景
\033[0m     : 取消属性设置

*/
using namespace std;

void draw1() 
{
    fprintf(stderr, "\033[%d;%dH", 10, 15); // 设置光标位置
    fprintf(stderr, "\033[41;33mHello world\033[0m\n");
}
void draw2() 
{
    fprintf(stderr, "\033[%d;%dH", 16, 15);
    fprintf(stderr, "\033[41;33mHello world\033[0m\n");
}

int main(int argc, char const *argv[])
{
    
    draw1();
    draw2();
    

    return 0;
}
