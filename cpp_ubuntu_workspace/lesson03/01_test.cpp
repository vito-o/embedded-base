#include <iostream>

using namespace std;

void change_value_quote(int &quote)
{
    cout << "change_value_quote addr: " << &quote << endl;

    quote = 800;
}

string &method()
{
    static string str = "hello world";
    return str;
}

void printf_string(string str)
{
    cout << "str: " << str << endl;
}

// 引用
int main(int argc, char const *argv[])
{
    /* 
    int data = 100;
    int &quote = data;  // quote 是data 的引用(别名)

    cout << "data addr : " << &data << endl;
    cout << "quote addr: " << &quote << endl;
    // data addr : 0x7ffc3987b81c
    // quote addr: 0x7ffc3987b81c

    quote = 200;

    cout << "data : " << data << endl;
    cout << "quote: " << quote << endl;

    data = 300;
    change_value_quote(quote);

    cout << "data : " << data << endl;
    cout << "quote: " << quote << endl;
 */

    /* 
    // 对数组的引用
    int a[3] = {1,2,3};
    int (&b)[3] = a;
    cout << "sizeof(b) : " << sizeof(b)  << endl; */

    /* 
    // 引用作为函数返回值
    string str = method();
    cout << str << endl; */

    // int a = 10;
    // const int &new_a = a; // 常引用
    // // new_a = 100; error

    // const int &c = 15;  // 常引用 
    // //int &a = 20; error 

    string str = "hello";
    printf_string(str);
    printf_string("world");

    return 0;
}
