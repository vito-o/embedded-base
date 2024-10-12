#include <iostream>
#include <set>

using namespace std;

int main(int argc, char const *argv[])
{
    set<int> s1;    //不能重复

    s1.insert(12);
    s1.insert(12);
    s1.insert(10);
    s1.insert(9);

    for(set<int>::iterator it = s1.begin(); it != s1.end(); it++) {
        cout << *it << endl;
    }

    cout << "---------------------------------" << endl;

    multiset<int> s2; //可以重复

    s2.insert(12);
    s2.insert(12);
    s2.insert(10);
    s2.insert(9);

    for(multiset<int>::iterator it = s2.begin(); it != s2.end(); it++) {
        cout << *it << endl;
    }

    return 0;
}
