#include <iostream>
#include <string.h>
/*

\033[%d;%dH : 设置光标位置
\033[41;33m : 设置字体颜色和背景
\033[0m     : 取消属性设置

*/
using namespace std;

void draw(int w, int h, const int background, int color, const char *str) 
{
    // printf("w = %d, h = %d\n", w, h);
    fprintf(stderr, "\033[%d;%dH", h, w); // 设置光标位置
    fprintf(stderr, "\033[%d;%dm%s\033[0m\n", background, color, str); 
}

int main(int argc, char const *argv[])
{
    int width = 11;
    int height = 11;

    int left_offset = 4;
    int top_offset = 3;

    int color = 0;
    int background = 0;
    const char str[] = "*";

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            //左斜线
            if (row == col) {
                background = 45;
                color = 37;
                draw(col+left_offset, row+top_offset, background, color, str);
            }
            // 右斜线
            if (row + col == 10) {
                background = 44;
                color = 37;
                draw(col+left_offset, row+top_offset, background, color, str);
            }
            // 竖线
            if (5 == col) {
                background = 42;
                color = 30;
                draw(col+left_offset, row+top_offset, background, color, str);
            }
            // 横线
            if (5 == row) {
                background = 43;
                color = 30;
                draw(col+left_offset, row+top_offset, background, color, str);
            }
            // 中心点
            if (col == 5 && row == 5) {
                background = 41;
                color = 37;
                draw(col+left_offset, row+top_offset, background, color, str);
            }
        }
    }

    
    
    

    return 0;
}
