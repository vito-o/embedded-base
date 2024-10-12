#ifndef __LUBAN_H__
#define __LUBAN_H__

#include <iostream>

#include "Hero.h"
#include "Shooter.h"
#include "Skin.h"

using namespace std;

class Luban: public Hero, public Shooter {
    public:
        Luban(const string &name, int distance, int legLen);
        ~Luban();
        void show(); 

    private:
        int legLen;
        Skin skin;
};

#endif