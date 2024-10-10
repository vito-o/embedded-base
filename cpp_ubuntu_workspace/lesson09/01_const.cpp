#include <iostream>
// 类中const 属性赋值 使用 构造函数参数列表中进行初始化
using namespace std;

class Test 
{

public:
    Test(int a, int b):b(b)
    {
        this->a = a;
    }

    void show()
    {
        cout << "a : " << a << endl;
        cout << "b : " << b << endl;
    }
    void show_() const
    {
        cout << "show() const : " << endl;
    }

    void function(void) const; // const修改的成员函数 不能修改成员变量的值

private:
    int a;
    const int b;

};

void Test::function(void) const
{
    // a++;    //error: increment of member ‘Test::a’ in read-only object
    int c = 0;
    c++;

}

int main(int argc, char const *argv[])
{
    Test obj(2, 3);
    obj.show();

    // const 修饰的对象, 只能调用const函数
    const Test other(3, 5);
    other.show_();   //error: passing ‘const Test’ as ‘this’ argument discards qualifiers

    return 0;
}
