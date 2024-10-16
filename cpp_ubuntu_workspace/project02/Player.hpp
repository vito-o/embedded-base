#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>

using namespace std;

class Player 
{
    public:
        Player(const string &name, const string &color)
        {
            this->name = name;
            this->color = color;
        }

        string getName(void) const
        {
            return name;
        }

        string getColor(void) const
        {
            return color;
        }

        virtual bool placeChess(int x, int y) = 0;

    private:
        string name;
        string color;
};

#endif