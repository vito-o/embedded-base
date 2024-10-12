#include <iostream>
#include <stack>

using namespace std;
// 栈 先进后出
int main(int argc, char const *argv[])
{
    stack<string> q;

    q.push("abc1");
    q.push("abc2");
    q.push("abc3");

    while(!q.empty()) {
        cout << q.top() << endl;
        q.pop();
    }
    return 0;
}
