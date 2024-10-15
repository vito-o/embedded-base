#include <iostream>

using namespace std;

// 饿汉式
class HungrySingleton {
    public:
        static HungrySingleton *getInstance() {
            return object;
        }
        void show()
        {
            cout << "HungrySingleton::show()" << endl;
        }

    protected:
        HungrySingleton() {
            cout << "HungrySingleton()" << endl;
        }
        HungrySingleton(const HungrySingleton &other) { //拷贝构造
            *this = other;
        }

    private:
        static HungrySingleton *object;
};

HungrySingleton *HungrySingleton::object = new HungrySingleton;


int main(int argc, char const *argv[])
{
    cout << "-----------------------------" << endl;
    HungrySingleton *obj = HungrySingleton::getInstance();
    cout << obj << endl;
    obj->show();

    HungrySingleton *obj1 = HungrySingleton::getInstance();
    cout << obj1 << endl;
    obj1->show();

    return 0;
}
