#ifndef __GIRL_H__
#define __GIRL_H__

#include <iostream>

using namespace std;

class Girl
{
    public:
        Girl(const string &name): name(name) {}
        virtual void marry(int money) = 0;

    protected:
        string name;
};

#endif