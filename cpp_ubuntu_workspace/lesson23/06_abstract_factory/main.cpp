#include "AndroidFactory.hpp"

#include "AppleFactory.hpp"

int main(int argc, char const *argv[])
{
    AndroidFactory *androidFactory = new AndroidFactory;
    AbstractPhone *android = androidFactory->getPhone();
    AbstractShell *androidShell = androidFactory->getShell();

    AppleFactory *appleFactory = new AppleFactory;
    AbstractPhone *apple = appleFactory->getPhone();
    AbstractShell *appleShell = appleFactory->getShell();

    androidShell->protect();
    android->call();
    android->message();

    cout << "-----------------------------------------------" << endl;

    appleShell->protect();
    apple->call();
    apple->message();


    return 0;
}
