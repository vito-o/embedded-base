#include <iostream>
// 友元类
// 把类A声明为类B的友元类,这样这个类A的所有成员函数都可以访问类b的私有成员
// 

using namespace std;

class B;

class A {
    public:
        void function1(const B &obj);
        void function2(B &obj);
};

class B {
    private:
        friend class A;
        int b;
};


void A::function1(const B &obj)
{
    cout << "function1 obj.b : " << obj.b << endl;
}
void A::function2(B &obj)
{
    cout << "function2 obj.b : " << obj.b << endl;
}

int main(int argc, char const *argv[])
{
    A a_obj;
    B b_obj;

    a_obj.function1(b_obj);
    a_obj.function2(b_obj);

    return 0;
};
