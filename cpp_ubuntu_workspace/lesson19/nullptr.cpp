#include <iostream>

/*
nullptr 关键字表示空指针
NULL通常在c语言中与处理宏定义为(void *)0或者0, 这样0就有int型常量和空指针的双重身份，为了避免这个歧义，c++11重新定义了一个新关键字nullptr，充当单独空指针常量

*/
using namespace std;

class Test 
{
    public:
        void TestWork(int index)
        {
            cout << "TestWork 1" << endl;
        }
        void TestWork(int *index)
        {
            cout << "TestWOrk 2" << endl;
        }
};

int main(int argc, char const *argv[])
{

    Test test;

    // TestWork   error: call of overloaded ‘TestWork(NULL)’ is ambiguous
    // test.TestWork(NULL);
    test.TestWork(nullptr);

    return 0;
}
