#include <iostream>
//1. lambda 隐式值捕获
// 我们还可以让编译器根据函数体中的代码来推断需要捕获那些变量，这种方式称之为隐式捕获。
// 隐式捕获有两种方式，分别是[=]和[&]。 
// [=] 表示以值捕获的方式捕获外部变量
// [&] 表示以引用捕获的方式捕获外部变量
using namespace std;

int main(int argc, char const *argv[])
{
    int c;
    int a = 100;

    // auto lamda = [=] {  // [=]
    auto lamda = [&] {  // [=]
        int result = a + 10;
        return result;
    };

    a = 200;
    c = lamda();    // [=]捕获  c = 110 , [&]捕获 c = 210

    cout << "a = " << a << endl;
    cout << "c = " << c << endl;

    return 0;
}
