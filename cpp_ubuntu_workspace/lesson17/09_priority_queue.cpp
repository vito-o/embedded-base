#include <iostream>
#include <queue>

using namespace std;
// 优先队列 大数在前小树在后
int main(int argc, char const *argv[])
{
    priority_queue<int> q;

    for(int i = 0; i < 20; i++) {
        q.push(rand()%100 + 1);
    }

    while(!q.empty()) {
        cout << q.top() << endl;
        q.pop();
    }
    return 0;
}
