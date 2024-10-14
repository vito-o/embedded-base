#include <iostream>
#include <memory>
// 使用 weak_ptr 和 shared_ptr 解决循环引用问题
using namespace std;

class BB;

class AA
{
    public:
        AA() { cout << "AA()" << endl;}
        ~AA() { cout << "~AA()" << endl;}
        weak_ptr<BB> m_bb_ptr;
};

class BB
{
    public:
        BB() { cout << "BB()" << endl;}
        ~BB() { cout << "~BB()" << endl;}
        shared_ptr<AA> m_aa_ptr;
};

int main(int argc, char const *argv[])
{
    shared_ptr<AA> a_ptr(new AA);
    shared_ptr<BB> b_ptr(new BB);

    cout << "a_ptr use count : " << a_ptr.use_count() << endl;
    cout << "b_ptr use count : " << b_ptr.use_count() << endl;

    cout << "------------------------------" << endl;

    a_ptr->m_bb_ptr = b_ptr;
    b_ptr->m_aa_ptr = a_ptr;

    cout << "a_ptr use count : " << a_ptr.use_count() << endl;
    cout << "b_ptr use count : " << b_ptr.use_count() << endl;

    return 0;
}
