#include <iostream>
#include <map>
// c11中对for进行优化， 
using namespace std;

int main(int argc, char const *argv[])
{
    map<string, int> m{{"a", 1}, {"b", 2}, {"c", 3}};

    for (auto p : m) {
        cout << p.first << " : " << p.second << endl;
    }

    return 0;
}
