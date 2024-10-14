#include <iostream>

using namespace std;

/*
右值一般都是临时对象的形式存在，他是没有名字的，所以想找到他只能通过引用的方式，而这就引入了c++中右值引用（T&&）的概念

类型&& 引用变量名字 = 右值；

注意：
与引用一样，右值引用在定义时必须初始化。通常情况下，右值引用不能引用左值

*/

int main(int argc, char const *argv[])
{
    
    const int &a = 10;
    int &&b = 10;

    //a++; //error: increment of read-only reference ‘a’
    b++;

    return 0;
}
