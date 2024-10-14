#include <iostream>
#include <assert.h>

/*
static_assert是在编译期间的断言，即编译器期间发现断言条件不成立，立即编译报错
static_assert(bool_constexpr, string)

bool_constexpr: 常量表达式（不能包含变量）
string: 如果bool_constexpr表达式为false， 这个string就是编译时候报的错误


static_assert的断言表达式的结果必须是在编译时期可以计算的表达式，即必须是常量表达式

// run-time assert
assert(ptr != NULL);

c++ 11
// compile-time assert
static_assert(sizeof(void *) == 4, "64-bit is not support");

*/

using namespace std;

int main(int argc, char const *argv[])
{
    string *ptr = nullptr;

    // 在运行期间才进行报错
    // assert.cpp:27: int main(int, const char**): Assertion `ptr != NULL' failed.
    // assert(ptr != NULL);

    // 编译器间报错, 因为ptr是变量，
    // static_assert(ptr != nullptr, "ptr is nullptr")

    static_assert(sizeof(void *) == 8, "64-bit is not support");

    return 0;
}

