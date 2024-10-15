#ifndef __SIMPLE_FACTORY_H__
#define __SIMPLE_FACTORY_H__

#include "AndroidPhone.hpp"
#include "ApplePhone.hpp"

using namespace std;

class SimpleFactory
{
    public:
        static AbstractPhone *getPhone(const string &name)
        {
            if (name == "Android") {
                return new AndroidPhone;
            } else if (name == "Apple") {
                return new ApplePhone;
            }
            return nullptr;
        }
};

#endif