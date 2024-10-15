#ifndef __ANDROID_PHONE_H__
#define __ANDROID_PHONE_H__

#include <iostream>
#include "Phone.hpp"

using namespace std;

class AndroidPhone : public AbstractPhone
{
    public:
        virtual void call(void)
        {
            cout << "android call" << endl;
        }

        virtual void message(void)
        {
            cout << "android message" << endl;
        }
};

#endif