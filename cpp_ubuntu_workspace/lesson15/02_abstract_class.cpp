#include <iostream>
// 抽象类
// 方法不实现 而是 = 0
// 派生类必须实现基类的抽象方法， 不然子类也是抽象类

using namespace std;

class A {
    public:
        virtual void function(void) = 0;  // 抽象类， 方法不实现 而是 = 0
};

class B : public A {
    public:
        void show(void) 
        {
            cout << "B:show()" << endl;
        }

        void function() 
        {
            cout << "B: function" << endl;
        }
};

int main(int argc, char const *argv[])
{
    B obj;
    obj.show();

    return 0;
}

