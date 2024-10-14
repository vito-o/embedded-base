#include <iostream>
//lambda 基础使用
using namespace std;

int main(int argc, char const *argv[])
{
    int a = 10;
    int b = 20;
    auto lamda = [a, b](int c, int d)mutable ->int{
        if (d == 0) {
            throw(10);
        }

        a++;
        b++;

        cout << "a: " << a << endl;
        cout << "b: " << b << endl;
        return (a + b + c/d);
    };

    try {
        lamda(2, 0);
    } catch(int error) {
        cout << "error: " << error << endl;
    }

    try {
        cout << "lamda result : " << lamda(12, 4) << endl;
    } catch(int error) {
        cout << "error: " << error << endl;
    }

    return 0;
}
