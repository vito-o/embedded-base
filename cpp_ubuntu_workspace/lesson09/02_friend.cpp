#include <iostream>
// 友元函数 
// class的私有属性,在外部方法中赋值,可以使用友元函数
// - friend void change_value(A &obj);

using namespace std;

class A
{
friend void change_value(A &obj);

private:
    int a;

public:
    void show(void) const
    {
        cout << "a : " << a << endl;
    }

};

void change_value(A &obj)
{
    obj.a = 100;
}

int main(int argc, char const *argv[])
{
    A a_obj;

    change_value(a_obj);

    a_obj.show();

    return 0;
};
