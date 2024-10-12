#include <iostream>
#include <queue>

using namespace std;
// 队列 先进先出
int main(int argc, char const *argv[])
{
    queue<string> q;

    q.push("abc1");
    q.push("abc2");
    q.push("abc3");

    while(!q.empty()) {
        cout << q.front() << endl;
        q.pop();
    }
    return 0;
}
