#include <iostream>
#include <map>

using namespace std;

int main(int argc, char const *argv[])
{
    multimap<string, int> m1;

    m1.insert(pair<string,int>("x", 13));
    m1.insert(pair<string,int>("y", 234));
    m1.insert(pair<string,int>("y", 64));
    m1.insert(pair<string,int>("efg", 300));


    multimap<string, int>::iterator it = m1.find("y");
    if (it != m1.end()) {
        cout << it->first << "." << it->second << endl;
    }

    cout << "-------------------------------" << endl;
    // 找key相同的所有值
    pair<multimap<string, int>::iterator, multimap<string, int>::iterator> range = m1.equal_range("y");
    for (multimap<string,int>::iterator it = range.first; it != range.second; it++){
        cout << it->first << "." << it->second << endl;
    }

    return 0;
}
