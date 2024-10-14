#include <iostream>
#include <functional>
/*
std::bind
将可调用对象与其参数一起进行绑定，绑定后的结果可以使用std::function保存。
std::bind主要有以下两个作用：
1.将可调用对象和其参数绑定成一个仿函数
2.只绑定部分参数，减少可调用对象传入的参数

bing本质是一个函数模板，一共两个参数
- 参数f表示可调用对象
- 参数__args表示要绑定的参数列表，使用std::placeholders::_x作为占位符
为绑定参数使用命名空间std::placeholders的占位符 _1,_2,_3...所代替

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

    cout << "----------------------------------------------------" << endl;

    // cout << std_function(add, 10, 20) << endl;
    // cout << std_function(divide(), 10, 20) << endl;
    // cout << std_function(object, 10, 20) << endl;
    // cout << std_function(mod, 10, 20) << endl;

    cout << "----------------------------------------------------" << endl;

    auto a = std::bind(add, 10, 20);
    cout << a() << endl;

    auto b = std::bind(divide(), std::placeholders::_1, std::placeholders::_2);
    cout << b(10, 3) << endl;

    auto c = std::bind(mod, 10, 20);
    cout << c() << endl;

    auto d = std::bind(&Calc::add, &object, 100, std::placeholders::_1);
    cout << d(150) << endl;

    cout << "----------------------------------------------------" << endl;
    // 使用std_function包装器进行包装
    cout << std_function(bind(&Calc::add, &object, placeholders::_1, placeholders::_2), 10, 20) << endl;
    return 0;
}
