#include <iostream>

using namespace std;

class A {
    public:
        int a1;
    protected:
        int a2;
    private:
        int a3;
};

#if 0
// 公有继承
class B : public A{
    public:
        void function(void)
        {
            a1 = 100;
            a2 = 200;
            // private 只能在类内部私有访问
            // a3 = 300; // error: ‘int A::a3’ is private within this context
        }
};

int main(int argc, char const *argv[])
{
    B obj;
    obj.a1 = 100;
    // protected 只能在家族内部访问
    // obj.a2 = 200; // error: ‘int A::a2’ is protected within this context
    
    return 0;
}

#endif

#if 0
// 保护继承
class B : protected A{
    public:
        void function(void)
        {
            a1 = 100;
            a2 = 200;
        }
};

int main(int argc, char const *argv[])
{
    B obj;
    // obj.a1 = 100;   // error: ‘int A::a1’ is inaccessible within this context
    
    return 0;
}
#endif


// 私有继承
class B : private A{
    public:
        void function(void)
        {
            a1 = 100;
            a2 = 200;
        }
};

int main(int argc, char const *argv[])
{
    B obj;
    // obj.a1 = 100;   // error: ‘int A::a1’ is inaccessible within this context
    
    return 0;
}
