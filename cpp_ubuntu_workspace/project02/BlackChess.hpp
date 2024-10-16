#ifndef __BLACK_CHESS_H__
#define __BLACK_CHESS_H__

#include <stdio.h>
#include "Chess.hpp"

class BlackChess: public Chess
{
    public:
        BlackChess(int x, int y): Chess("black", x, y) {};
        void show(void) const 
        {
            fprintf(stderr, "\033[%d;%dH\033[43;35m[☻]\033[0m", getY(), getX() - 1);
            fprintf(stderr, "\033[%d;%dH", getY(), getX());
        }
};

#endif