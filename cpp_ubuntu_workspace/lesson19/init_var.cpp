#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main(int argc, char const *argv[])
{
    // 在c++11之前，只有数组能初始化列表，其他容器想要使用初始化列表，只能用以下方法
    int arr[3] = {1,2,3};
    vector<int> v(arr, arr+3);

    for(auto it = v.begin(); it != v.end(); it++) {
        cout << *it << endl;
    }

    cout << "--------------------------------------" << endl;

    // 在c++11后，我们使用以下语法来进行替换
    int arr[3] {1,2,3};
    vector<int> v{2, 3, 4};
    map<int, string> {{1, "a"}, {2, "b"}};
    string str{"hello world"};

    class Test{
        private:
            int a{10};
            string b {"hellow"};
    }; 

    return 0;
}
