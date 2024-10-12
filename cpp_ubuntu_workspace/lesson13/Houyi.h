#ifndef __HOUYI_H__
#define __HOUYI_H__

#include <iostream>

#include "Hero.h"
#include "Shooter.h"
#include "Skin.h"

using namespace std;

class Houyi: public Hero, public Shooter {
    public:
        Houyi(const string &name, int distance, int legLen);
        ~Houyi();
        void show(); 
        virtual void skill();

    private:
        int legLen;
        Skin skin;
};

#endif