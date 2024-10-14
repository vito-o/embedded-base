#include <iostream>
#include <string.h>
#include <memory>
// autoptr 智能指针, 自动释放堆区创建的对象


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
    
#if 0
    String *obj = new String("helloworld");
    obj->show();
#endif

    auto_ptr<String> smart1(new String("hello"));
    auto_ptr<String> smart2(new String("hello"));

    smart1->show();
    (*smart2).show();

    

    return 0;
}
