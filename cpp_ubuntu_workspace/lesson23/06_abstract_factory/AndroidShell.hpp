// AndroidShell.hpp

#ifndef __ANDROID_SHELL_H__
#define __ANDROID_SHELL_H__

#include <iostream>
#include "Shell.hpp"

using namespace std;

class AndroidShell: public AbstractShell
{
    public:
        virtual void protect(void)
        {
            cout << "Android shell protect" << endl;
        }
};

#endif