#include <iostream>

using namespace std;

class Test {
    public:
        void function() {
            cout << "hello" << endl;
        }
        virtual void vir_function() {
            cout << "vir_function" << endl;
        }

    private:
        int a;
        static int b;
};

int Test::b = 0;
int main(int argc, char const *argv[])
{
    Test obj;
    cout << "sizeof(obj) = " << sizeof(obj) << endl;


    return 0;
}
