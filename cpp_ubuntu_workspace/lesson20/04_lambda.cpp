#include <iostream>
//1. lambda 省略参数，表示不传参数
using namespace std;

int main(int argc, char const *argv[])
{
    int a = 10;
    int b = 20;
    auto lamda = [a, b] {
        cout << "a: " << a << endl;
        cout << "b: " << b << endl;
        return (a + b);
    };

    cout << "lamda result : " << lamda() << endl;

    return 0;
}
