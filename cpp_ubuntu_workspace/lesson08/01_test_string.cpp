#include <iostream>
#include <string.h>

using namespace std;

class String
{
public:
    String(const char *str = NULL);
    String(const String &obj);
    ~String(); //析构函数
    void show(void);

private:
    char *str;
};


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

// 对于普通函数的传参
// void function(String object); //调用拷贝构造函数
// void function(String &object); //不调用拷贝构造函数
// void function(String *object); //不调用拷贝构造函数

// 函数返回一个对象的时候
String function(void)
{
    String object("hello");
    return object;
    // 返回一个对象的时候,会调用拷贝构造函数,
    // 注意:有些时候g++编译器会优化代码,不创建临时对象,看不到调用拷贝构造函数的现象.可以在编译时候加上-fno-elide-constructors编译参数,让编译器不要做此优化
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

void function(String object)
{
    object.show();
}

int main(int argc, char const *argv[])
{
    
    String str1("he");
    String str2 = str1;
    cout << "---------------------------" << endl;
    str1.show();
    cout << "---------------------------" << endl;
    str2.show();
    cout << "---------------------------" << endl;
    function(str1);
    cout << "---------------------------" << endl;
    return 0;
}
