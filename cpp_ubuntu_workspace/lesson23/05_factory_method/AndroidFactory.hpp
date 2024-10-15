#ifndef __ANDROID_FACTORY_H__
#define __ANDROID_FACTORY_H__

#include "PhoneFactory.hpp"
#include "AndroidPhone.hpp"

using namespace std;

class AndroidFactory: public PhoneFactory
{
    public:
        virtual AndroidPhone *CreateProduct()
        {
            return new AndroidPhone;
        }
};

#endif