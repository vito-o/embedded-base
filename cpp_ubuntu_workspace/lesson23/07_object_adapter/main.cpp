#include <iostream>
#include "PowerAdapter.hpp"
#include "ChinaPlug.hpp"
// 适配器，就是将多个对象在一个类里面可以处理
using namespace std;

int main(int argc, char const *argv[])
{
    Plug *plug = new ChinaPlug;
    PowerAdapter *adapter = new PowerAdapter;
    adapter->setPlug(plug);

    cout << adapter->getOutput5V() << endl;

    return 0;
}
