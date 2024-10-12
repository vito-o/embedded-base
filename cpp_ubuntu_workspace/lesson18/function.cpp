#include <iostream>

using namespace std;
// 函数对象, cmp是一个对象，但是可以像函数一样调用
// STL内建了很多函数对象
// #include <functional>
// 算术仿函数
// 关系仿函数
// 逻辑仿函数

/*
使用函数对象的好处
- 通过函数对象调用operator(),可以通过内链省略函数的调用开销，比通过函数指针调用函数（不能内联）效率高
- 使用函数对象虽然我们没有显示加inline关键字，但是编译器优化时候可能会优化成内联
- 因为函数对象是用类生成的，所以类中可以添加相关的成员变量，用来记录函数对象使用时的更多信息

*/

class Compare
{
    public:
        bool operator()(int a, int b)
        {
            return a > b;
        }
};


int main(int argc, char const *argv[])
{
    
    Compare cmp;
    cout << cmp(1, 2) << endl;
    cout << cmp(3, 2) << endl;

    return 0;
}

