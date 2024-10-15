#ifndef __ABSTRACT_FACTORY_H_
#define __ABSTRACT_FACTORY_H_

#include "Phone.hpp"

class PhoneFactory
{
    public:
        virtual AbstractPhone *CreateProduct() = 0;
};


#endif