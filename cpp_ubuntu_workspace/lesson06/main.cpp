#include <iostream>
#include "as.h"

using namespace std;

// gcc -fpic -shared add.c sub.c -o libas.so 编译动态库
// c++ 链接 c 函数动态"libas.so"库
// g++ main.cpp -L . -las;     // -L 动态库的位置;  -l 动态库的名字,这里虽然动态库全名较libas.so,但引用的时候用 掐头去尾用中间 as,
// nm libas.so, 可以看动态库内容
// readelf -a a.out 可以看a.out里面的内容
int main(int argc, char const *argv[])
{
    int result;

    result = add(10, 20);
    cout << "add(10, 20) = " << result << endl;

    result = sub(30, 20);
    cout << "sub(30, 20) = " << result << endl;

    return 0;
}
