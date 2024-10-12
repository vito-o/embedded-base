#include <iostream>

using namespace std;
// 函数模板非类型 参数
template <typename T, unsigned int m, unsigned int n>
int function(const T (&ra1)[m], const T (&ra2)[n])
{
    cout << m << "," << n << endl;
    return 0;
}

int main(int argc, char const *argv[])
{
    int a[10];
    int b[20];

    function<int, 10, 20>(a, b);


    return 0;
}
