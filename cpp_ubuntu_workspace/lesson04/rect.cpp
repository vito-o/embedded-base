#include <iostream>

using namespace std;
// 函数单独声明,默认值放在声明中
extern void drawREct(int x, int y, int width = 10, int height = 10);

int main(int argc, char const *argv[])
{
    drawREct(0, 0);
    cout << "-----------------------------" << endl;
    drawREct(10, 15);
    cout << "-----------------------------" << endl;
    drawREct(20, 10, 100, 200);
    cout << "-----------------------------" << endl;

    return 0;
}


void drawREct(int x, int y, int width, int height)
{
    cout << "x: " << x << "y: " << y << endl;
    cout << "width: " << width << "height: " << height << endl;
}