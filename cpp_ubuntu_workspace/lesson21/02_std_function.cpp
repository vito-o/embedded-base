#include <iostream>
#include <functional>
// 01中几种可调用对象虽然类型不同，但是共享了一种调用形式
// int (int, int)
// 通过std::function 将上述类型保存起来，使得使用起来更方便


/*
std::function是一个可调用对象包装器， 是一个类模板，可以容纳除了类成员函数指针之外的所有可调用对象，
它可以用统一的方式处理函数、函数对象、函数指针，并允许保存和延迟他们的执行

// 格式
std::function<函数类型> = 可调用对象

std::function<int(int, int)> a = add;
std::function<int(int, int)> b = mod;
std::function<int(int, int)> c = divide;

*/

using namespace std;

// 普通函数
int add(int a, int b)
{
    return a + b;
}

// 函数对象类
class divide
{
    public:
        int operator()(int denominator, int divisor) {
            return denominator / divisor;
        }
};

class Calc
{
    public:
        // 类对象转化成函数指针类型
        // 定义一个函数指针类型 ftype，指向返回类型为 int，参数为两个 int 的函数

        // 这里使用 using 定义了一个新的类型 ftype，它实际上是一个函数指针类型。
        // 这个指针指向的是返回类型为 int 且接受两个 int 参数的函数。也就是说，ftype 可以表示任何形如 int func(int, int) 的函数指针。
        using ftype = int (*)(int,int);

        // 定义一个类型转换运算符，将 Calc 对象转换为 ftype 类型（即 int (*)(int, int) 函数指针类型）
        // 这里定义了一个类型转换运算符，使得 Calc 对象可以被隐式转换为 ftype 类型的函数指针。

        // operator ftype() 表示将 Calc 类型转换为 ftype 类型。
        operator ftype() {return ::add;}; //::add 这样写是调用 这个类外面的add函数，

        int add(int a, int b)
        {
            return a + b;
        }
};

// 类成员函数指针： int (Calc *obj, int (Calc::*func)(int a, int b)
int calc_function(Calc *obj, int (Calc::*func)(int a, int b),
                    int data1, int data2)
{
    return (obj->*func)(data1, data2);
}

// ----------------------------------------------------------------------

int std_function(function<int (int, int)> func_obj, int a, int b)
{
    return func_obj(a, b);
}


int main(int argc, char const *argv[])
{   
    Calc object;
    // lambda 表达式
    auto mod = [](int a, int b) { return a % b;};
    // cout << mod(10, 3) << endl;

    // cout << add(10, 20) << endl;
    // cout << divide()(40, 20) << endl;

    // cout << object.add(10, 20) << endl;
    // cout << object(10, 20) << endl;
    // cout << calc_function(&object, &Calc::add, 100, 200) << endl;

    cout << std_function(add, 10, 20) << endl;
    cout << std_function(divide(), 10, 20) << endl;
    cout << std_function(object, 10, 20) << endl;
    cout << std_function(mod, 10, 20) << endl;


    return 0;
}
