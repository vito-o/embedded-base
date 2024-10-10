#include <iostream>
#include <string.h>

using namespace std;

class String
{
public:
    // String();
    String(const char *str = NULL);
    ~String(); //析构函数
    void show(void);

private:
    char *str;
};

// String::String() {}

String::String(const char *str)
{
    if (str) 
    {
        int len = strlen(str) + 1;
        cout << "len = " << len << endl;
        // this->str = (char *)malloc(len);
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
    // while (this->str[i++])
    for (char *p = str; p && *p; p++)
    {
        // cout << "str[" << i << "] = " << this->str[i] << "::" << (int)this->str[i] << endl;
        cout << *p << "::" << (int)*p << endl;
    }
    
}

int main(int argc, char const *argv[])
{
    
    String str("hello world!");
    str.show();

    return 0;
}
