#ifndef __APPLE_FACTORY_H__
#define __APPLE_FACTORY_H__

#include "PhoneFactory.hpp"
#include "ApplePhone.hpp"

using namespace std;

class AppleFactory: public PhoneFactory
{
    public:
        virtual ApplePhone *CreateProduct()
        {
            return new ApplePhone;
        }
};

#endif