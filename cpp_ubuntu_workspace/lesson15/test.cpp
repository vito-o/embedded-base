#include <iostream>
// 虚析构函数
/*
1.基类虚构函数不是虚构函数时free_function， 直接调用A类的虚构函数
2.基类析构函数是虚函数时free_function, 动态获取要调用的函数， B的析构函数自动成为虚函数，出现在虚函数表中

总结：
- 将基类的析构函数声明为虚函数，则派生类的析构函数自动为虚函数
- 基类的指针或引用指向派生类对象的时候，可以通过删除基类指针调用派生类析构函数或基类析构函数，防止资源未释放
- 建议将基类的析构函数声明为虚函数，防止在多态场合造成资源未释放问题


*/


using namespace std;

class A {
    public:
        A() {
            cout << "A()" << endl;
            aptr = new char[100];
        }

        // ~A() {
        virtual ~A() { // 虚析构函数
            cout << "~A()" << endl;
            delete [] aptr;
        }

    private:
        char *aptr;
};

class B : public A {
    public:
        B() {
            cout << "B()" << endl;
            bptr = new char[100];
        }

        ~B() {
            cout << "~B()" << endl;
            delete [] bptr;
        }
    private:
        char *bptr;
};

void free_function(A *p)
{
    delete p;
}

int main(int argc, char const *argv[])
{
    A *aobject = new A;
    free_function(aobject);

    cout << "--------------------------" << endl;

    B *bobject = new B;
    free_function(bobject);

    return 0;
}
