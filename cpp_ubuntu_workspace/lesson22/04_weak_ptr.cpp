#include <iostream>
#include <string.h>
#include <memory>
// weak_ptr 智能指针, 自动释放堆区创建的对象
// 它是对对象的一种弱引用，不会增加对象的引用技术，他可以从一个shared_ptr或另一个weak_ptr产生
// 没有重载* 和 -> ， 所以不能通过他访问对象内部的成员

/*
内部成员函数：
- expired: 用于检测所管理对象是否已经释放，如果已经释放，返回true，否则返回false
- lock: 用于获取所管理对象的强引用(shared_ptr)， 如果expired为true，返回一个空的shared_ptr； 否则返回一个shared_ptr，其内部对象指向与weak_ptr相同。
- use_count: 返回shared_ptr共享的对象的引用技术
- reset: 将weak_ptr置空

weak_ptr支持拷贝或赋值，但不会影响对象的shared_ptr内部对象的计数

*/

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
    cout << "String::String(const char *str)" << endl;

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

int main(int argc, char const *argv[])
{
    
    weak_ptr<String> w_smart;
    shared_ptr<String> s_smart(new String("hell"));

    w_smart = s_smart;
    cout << "w_smart = " << w_smart.use_count() << endl; // 查看引用计数的数量

    // w_smart->show(); 报错，不能通过weak_par 调用函数， 因为它没有对这个运算符做重载

    // 只能通过这种方式调用
    if (!w_smart.expired()) {
        shared_ptr<String> ptr = w_smart.lock();
        ptr->show();
    }
    


    
 
    return 0;
}
