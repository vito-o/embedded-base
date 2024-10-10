#include <iostream>
// 函数重载
using namespace std;

/* int add (int a, int b)
{
    return a + b;
} */
// 带默认值
int add (int a = 1, int b = 2)
{
    return a + b;
}
int add (int a, int b, int c)
{
    return a + b;
}
float add (float a, float b)
{
    return a + b;
}

int main(int argc, char const *argv[])
{
    cout << add(1, 2) << endl;
    cout << add(1, 2, 1) << endl;
    cout << add((float)1.3, (float)2.5) << endl;


    return 0;
}
