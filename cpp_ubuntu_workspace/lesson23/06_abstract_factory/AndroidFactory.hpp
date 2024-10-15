#ifndef __ANDROID_FACTORY_H__
#define __ANDROID_FACTORY_H__

#include "PhoneFactory.hpp"
#include "AndroidPhone.hpp"
#include "AndroidShell.hpp"

using namespace std;

class AndroidFactory: public PhoneFactory
{
    public:
        virtual AndroidPhone *getPhone()
        {
            return new AndroidPhone;
        }

        virtual AndroidShell *getShell()
        {
            return new AndroidShell;
        }
};

#endif