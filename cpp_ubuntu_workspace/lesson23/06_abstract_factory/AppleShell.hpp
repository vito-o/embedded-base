#ifndef __APPLE_SHELL_H__
#define __APPLE_SHELL_H__

#include <iostream>
#include "Shell.hpp"

using namespace std;

class AppleShell: public AbstractShell
{
    public:
        virtual void protect(void)
        {
            cout << "apple shell protect" << endl;
        }
};

#endif