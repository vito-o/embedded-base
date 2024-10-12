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

        // b = ++a, 加完后把a给b
        String &operator++();      // 前置++
        // b = a++  把a以前的值返回
        String operator++(int);    // 后置++(括号中需要个类型)
        // 下标运算符重构
        char &operator[](const int index);
        // 赋值运算符重构
        String &operator=(const String &other);
        // 左移运算符重构
        String &operator<<(const char *str);

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

// 前置++
String &String::operator++()
{
    cout << "String &String::operator++()" << endl;
    for(char *p = str; p && *p; p++)
    {
        *p = *p+1;
    }
    return *this;
}

// 后置++(括号中需要个类型)
String String::operator++(int)
{
    cout << "String &String::operator++(int)" << endl;
    String old(*this);
    for(char *p = str; p && *p; p++)
    {
        *p = *p+1;
    }
    return old;
}

// 下标赋值
char &String::operator[](const int index)
{
    cout << "String &String::operator[](const int index)" << endl;

    return str[index];
}

// 赋值运算符
String &String::operator=(const String &other)
{
    if (this == &other){
        return *this;
    }

    if (this->str) {
        delete [] this->str;
    }

    if (other.str) {
        int len = strlen(other.str) + 1;
        this->str = new char[len];
        strcpy(this->str, other.str);
    } else {
        this->str = NULL;
    }

    return *this;
}

// 左移运算符重构
String &String::operator<<(const char *str)
{   
    int len = 0;
    char *oldStr = NULL;

    if (!str) {
        return *this;
    }

    if (this->str) {
        len = strlen(this->str) + 1;
        oldStr = this->str;
    }

    len += strlen(str);
    this->str = new char[len];

    if (oldStr) {
        strcpy(this->str, oldStr);
        delete [] oldStr;
    } else {
        this->str[0] = '\0';
    }

    strcat(this->str, str);

    return *this;
}

int main(int argc, char const *argv[])
{
    // String str1("he");
    // String str2("llo");
    // String str3 = str1 + str2;
    // cout << "---------------------------" << endl;
    // cout << "---------------------------" << endl;
    // String str4 = str3++;
    // cout << "str3---------------------------" << endl;
    // str3.show();
    // cout << "str4---------------------------" << endl;
    // str4.show();
    // cout << "---------------------------" << endl;
    // cout << "---------------------------" << endl;
    // String str5 = (++str3);
    // cout << "str3---------------------------" << endl;
    // str3.show();
    // cout << "str5---------------------------" << endl;
    // str5.show();
    // cout << "---------------------------" << endl;
    // cout << "---------------------------" << endl;
    // str1[1] = 'M';
    // str1[2] = 'M';
    // str1[3] = 'M';
    // str1.show();

    // String str1("~llo");
    // String str2("@llo");
    // str1 = str2;
    // cout << "---------------------------" << endl;
    // str1.show();
    // cout << "---------------------------" << endl;
    // str2.show();
    // cout << "---------------------------" << endl;

    String str1("~llo");
    str1 << "asdf" << "~~asl35*(*)";
    str1.show();

    return 0;
}
