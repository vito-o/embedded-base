#ifndef __HERO_H__
#define __HERO_H__

#include <iostream>

using namespace std;

class Hero {
    public:
        Hero(const string &name = "hero");
        ~Hero();
        virtual void skill();

        string getName();

    private:
        string name;
};

#endif