#ifndef __APPLE_PHONE_H__
#define __APPLE_PHONE_H__

#include <iostream>
#include "Phone.hpp"

using namespace std;

class ApplePhone : public AbstractPhone
{
    public:
        virtual void call(void)
        {
            cout << "apple call" << endl;
        }

        virtual void message(void)
        {
            cout << "apple message" << endl;
        }
};

#endif