#ifndef __READ_GIRL_H__
#define __READ_GIRL_H__

#include "Girl.hpp"

class RealGirl : public Girl
{   
    public:
        RealGirl(const string &name = "cuihua"): Girl(name)
        {}

        virtual void marry(int money)
        {
            cout << "marry name: " << name << " marry money: " << money << endl;
        }
};

#endif