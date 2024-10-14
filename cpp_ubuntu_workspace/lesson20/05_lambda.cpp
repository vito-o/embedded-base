#include <iostream>
//1. lambda 值捕获和引用捕获的区别
using namespace std;

int main(int argc, char const *argv[])
{
    int c;
    int a = 100;

    // auto lamda = [a] { //值捕获
    auto lamda = [&a] { // 引用捕获
        int result = a + 10;
        return result;
    };

    a = 200;
    c = lamda();    // 值捕获  c = 110 , 引用捕获 c = 210

    cout << "a = " << a << endl;
    cout << "c = " << c << endl;

    return 0;
}
