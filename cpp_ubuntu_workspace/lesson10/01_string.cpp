#include <iostream>
#include <string.h>
// 运算符重载

using namespace std;

class String
{
    public:
        String(const char *str = NULL);
        String(const String &obj);
        ~String(); //析构函数
        void show(void);
        String operator+(const String &str2); // String str3 = str1.operator+(str2)
        friend String operator+(const String &str1, const String &str2);
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

// 写法一:
String operator+(const String &str1, const String &str2)
{
    String newStr;
    int len = strlen(str1.str) + strlen(str2.str) + 1;
    newStr.str = new char[len];
    strcpy(newStr.str, str1.str);
    strcat(newStr.str, str2.str);
    return newStr;
}

// 写法二:
String String::operator+(const String &str2)
{
    cout << "String String::operator+(const String &str2)" << endl;
    String newStr;
    int len = strlen(str) + strlen(str2.str) + 1;
    newStr.str = new char[len];
    strcpy(newStr.str, str);
    strcat(newStr.str, str2.str);
    return newStr;
}

int main(int argc, char const *argv[])
{
    String str1("he");
    String str2("llo");
    String str3 = str1 + str2;
    cout << "---------------------------" << endl;
    str3.show();
    cout << "---------------------------" << endl;
    return 0;
}
