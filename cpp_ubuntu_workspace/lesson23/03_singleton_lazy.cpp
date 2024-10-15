#include <iostream>
#include <pthread.h>

using namespace std;

// 懒汉式
// 优点：在使用的时候，才会分配内存创建对象
// 缺点：在多线程中使用，会出现创建多个对象的问题，线程不安全
// 解决方法：加锁

class LazySingleton {
    public:
        static LazySingleton *getInstance() {
            if (!object) {
                pthread_mutex_lock(&lock);
                if (!object) {
                    object = new LazySingleton;
                }
                pthread_mutex_unlock(&lock);
            }
            return object;
        }
        void show()
        {
            cout << "LazySingleton::show()" << endl;
        }

    protected:
        LazySingleton() {
            cout << "LazySingleton()" << endl;
        }
        LazySingleton(const LazySingleton &other) { //拷贝构造
            *this = other;
        }

    private:
        static LazySingleton *object;
        static pthread_mutex_t lock;
};

LazySingleton *LazySingleton::object = nullptr;
pthread_mutex_t LazySingleton::lock = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char const *argv[])
{
    cout << "-----------------------------" << endl;
    LazySingleton *obj = LazySingleton::getInstance();
    cout << obj << endl;
    obj->show();

    LazySingleton *obj1 = LazySingleton::getInstance();
    cout << obj1 << endl;
    obj1->show();

    return 0;
}
