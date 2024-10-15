#include "SimpleFactory.hpp"

int main(int argc, char const *argv[])
{
    AbstractPhone *android = SimpleFactory::getPhone("Android");
    AbstractPhone *apple = SimpleFactory::getPhone("Apple");

    android->call();
    android->message();
    apple->call();
    apple->message();


    return 0;
}
