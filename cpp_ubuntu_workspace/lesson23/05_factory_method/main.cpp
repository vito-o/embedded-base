#include "AndroidFactory.hpp"

#include "AppleFactory.hpp"

int main(int argc, char const *argv[])
{
    AndroidFactory *androidFactory = new AndroidFactory;
    AbstractPhone *android = androidFactory->CreateProduct();

    AppleFactory *appleFactory = new AppleFactory;
    AbstractPhone *apple = appleFactory->CreateProduct();


    android->call();
    android->message();
    apple->call();
    apple->message();


    return 0;
}
