#include <iostream>
#include <vector>
// auto 关键字， 让编译器自动推导类型  （复杂类型更适合）
// 限制：
// - auto 不能在函数的参数中使用
// - auto 不能作用于类的非静态成员变量（也就是没有static关键字修饰的成员变量）
// - auto 关键字不能定义数组
// - auto 不能作用于模板参数

using namespace std;



template<typename T>
class Test {

};

int main(int argc, char const *argv[])
{
    
    auto a = 90;
    auto b = 12.8;
    auto c = &a;
    auto str = "helloworld";
    int data = 100;

    vector<string> v;

    v.push_back("hello1");
    v.push_back("hello2");
    v.push_back("hello3");

    for (auto it = v.begin(); it != v.end(); it++) {
        cout << *it << endl;
    }

    // char url[] = "http://www.baidu.com";
    // auto str[] = url;

    Test<int> c1;
    // Test<auto> c2 = c1; // 错误


    return 0;
}
