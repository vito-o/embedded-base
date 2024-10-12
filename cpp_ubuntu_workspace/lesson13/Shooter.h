#ifndef __SHOOTER_H__
#define __SHOOTER_H__

#include <iostream>

using namespace std;

class Shooter {
    public:
        Shooter(int distance = 0);
        ~Shooter();

        int getDistance();

    private:
        int distance;
};

#endif