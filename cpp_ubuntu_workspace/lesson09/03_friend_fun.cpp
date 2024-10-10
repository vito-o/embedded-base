#include <iostream>
// 友元成员函数 
// 把类A的一个成员函数声明为类B的友元函数,这样这个类A的成员函数就可以访问类B的私有成员了
// 

using namespace std;

class B;

class A
{
public:
    void function(const B &obj);

};

class B 
{
private:
    friend void A::function(const B &obj);//只能先定义,后实现
    int b;
};


void A::function(const B &obj)
{
    cout << "obj.b : " << obj.b << endl;
}

int main(int argc, char const *argv[])
{
    A a_obj;
    B b_obj;

    a_obj.function(b_obj);

    return 0;
};
