#include <iostream>
//1. lambda 省略返回值类型，编译器在运行时可以自动推测出返回值类型
using namespace std;

int main(int argc, char const *argv[])
{
    int a = 10;
    int b = 20;
    auto lamda = [a, b](int c, int d) {
        if (d == 0) {
            cout << "d is invalid" << endl;
            return -1;
        }

        cout << "a: " << a << endl;
        cout << "b: " << b << endl;
        return (a + b + c/d);
    };

    cout << "lamda result : " << lamda(12, 4) << endl;

    return 0;
}
