#include <iostream>
// 泛型方法
using namespace std;

template <typename T>
void my_swap(T &a, T &b)
{
    T tmp;

    tmp = a;
    a = b;
    b = tmp;
}

int main(int argc, char const *argv[])
{
    int a = 10;
    int b=  20;

    // my_swap(a, b); // 自动类型推导
    my_swap<int>(a, b); // 显示指定类型  推荐这种

    cout << "a = " << a << " b = " << b << endl;

    cout << "---------------------------" << endl;

    string str1 = "aa";
    string str2 = "bb";

    my_swap(str1, str2);
    cout << "str1 = " << str1 << " str2 = " << str2 << endl;

    return 0;
}
