#include <iostream>
#include <vector>
/*
顺序容器的使用原则
- 如果你需要高效的随即存取，而不在乎插入和删除的效率，使用ector
- 如果你需要大量的插入和删除，而不关心随机存取，则使用list
- 如果你需要随机存取，而且关系两端数据的插入和删除，则应使用deque

*/
using namespace std;

int main(int argc, char const *argv[])
{
    vector<string> v1;

    v1.push_back("hello");
    v1.push_back("123");
    v1.push_back("234kj");

    for(int i = 0; i < v1.size(); i++) {
        cout << v1[i] << endl;
    }

    cout << "front: " << v1.front() << endl;
    cout << "back: " << v1.back() << endl;

    v1.pop_back();

    for (int i = 0; i < v1.size(); i++) {
        cout << v1[i] << endl;
    }

    cout << "---------------------------------" << endl;

    for (vector<string>::iterator it = v1.begin(); it != v1.end(); it++) {
        cout << *it << endl;
    }

    return 0;
}