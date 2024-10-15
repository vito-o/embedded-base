#ifndef __ABSTRACT_FACTORY_H_
#define __ABSTRACT_FACTORY_H_

#include "Phone.hpp"
#include "Shell.hpp"

class PhoneFactory
{
    public:
        virtual AbstractPhone *getPhone() = 0;
        virtual AbstractShell *getShell() = 0;
};


#endif