#ifndef __APPLE_FACTORY_H__
#define __APPLE_FACTORY_H__

#include "PhoneFactory.hpp"
#include "ApplePhone.hpp"
#include "AppleShell.hpp"

using namespace std;

class AppleFactory: public PhoneFactory
{
    public:
        virtual ApplePhone *getPhone()
        {
            return new ApplePhone;
        }
        virtual AppleShell *getShell()
        {
            return new AppleShell;
        }
};

#endif