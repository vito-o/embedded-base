#include <iostream>
#include <map>

using namespace std;

int main(int argc, char const *argv[])
{
    map<string, int> m1;

    m1["x"] = 1;
    m1["y"] = 2;
    m1.insert(pair<string,int>("efg", 300));

    cout << m1["x"] << endl;


    map<string, int>::iterator it = m1.find("y");
    if (it != m1.end()) {
        cout << it->first << "." << it->second << endl;
    }

    return 0;
}
