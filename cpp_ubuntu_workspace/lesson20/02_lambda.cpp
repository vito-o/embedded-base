#include <iostream>
//1. lambda 省略mutable   mutable， 表示对捕获的数据可修改， 去掉lambda中的捕获数据就变成常量了
using namespace std;

int main(int argc, char const *argv[])
{
    int a = 10;
    int b = 20;
    auto lamda = [a, b](int c, int d)->int{
        if (d == 0) {
            cout << "d is invalid" << endl;
            return -1;
        }

        // a++;
        // b++;

        cout << "a: " << a << endl;
        cout << "b: " << b << endl;
        return (a + b + c/d);
    };

    cout << "lamda result : " << lamda(12, 4) << endl;

    return 0;
}
