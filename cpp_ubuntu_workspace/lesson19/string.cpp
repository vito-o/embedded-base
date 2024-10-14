#include <iostream>
#include <string.h>
// 1.移动语义
// 2.std::move()， 
// - 它并不搬移任何东西，唯一的功能就是将一个左值强制转化为右值引用，通过右值引用使用该值，实现移动语义。 move更多是用在生命周期即将结束的对象上
// - 注意： 被转化的左值，其生命周期并没有随着左右值的转化而改变，即std:move转化的左值变量lvalue不会被销毁

using namespace std;

class String
{
    public:
        String(const char *str = NULL);
        String(const String &obj);
        ~String(); //析构函数
        void show(void);

        String(String &&obj);   // ---------*******-------------
        

    private:
        char *str;
};

// ---------*******-------------
String::String(String &&obj)
{
    cout << "String::String(String &&obj)" << endl;
    this->str = obj.str;
    obj.str = nullptr;
}
// ---------*******-------------

String::String(const char *str)
{
    if (str) 
    {
        int len = strlen(str) + 1;
        cout << "len = " << len << endl;
        this->str = new char[len];
        strcpy(this->str, str);
    }
    else
    {
        this->str = NULL;
    }
}

String::String(const String &obj)
{
    cout << "String(const String &obj)" << endl;
    if (obj.str)
    {
        int len = strlen(obj.str);
        str = new char[len];
        strcpy(str, obj.str);
    }
    else
    {
        this->str = NULL;
    }
}

// //析构函数, 在对象销毁的时候自动调用
String::~String()
{
    cout << "~String()" << endl;
    if (str)
    {
        delete [] str;
    }
}

void String::show()
{
    int i = 0;
    for (char *p = str; p && *p; p++)
    {
        cout << *p << "::" << (int)*p << endl;
    }
}

// ---------*******-------------
/*
移动语义： 以右值的方式，将函数内创建对象的返回值 直接引用出去，而不是创建临时对象拷贝，然后在用的地方在进行拷贝赋值，进行优化
*/
String GetString(const char* pStr)
{
    String strTemp(pStr);
    return strTemp;
}
// ---------*******-------------

// g++ string.cpp -fno-elide-constructors
int main(int argc, char const *argv[])
{
    
    String s1("hello");
    String s2(GetString("world"));

	s2.show();
	cout << "---------------------" << endl;

    // String s3(s2);       // 拷贝构造
    String s3(move(s2));    // 移动构造， 会导致两个对象用同一块堆区内存
    s3.show();

    return 0;
}
