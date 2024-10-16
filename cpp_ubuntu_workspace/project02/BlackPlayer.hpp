#ifndef __BLACK_PLAYER_H__
#define __BLACK_PLAYER_H__

#include "Player.hpp"
#include "ChessBoard.hpp"
#include "BlackChess.hpp"

class BlackPlayer: public Player
{
    public:
        BlackPlayer(const string &name):Player(name, "black") {}

        virtual bool placeChess(int x, int y)
        {
            ChessBoard *chessBoard = ChessBoard::getChessBoard();

            bool ok = chessBoard->isVaildPosition(x, y);
            if (ok)
            {
                chessBoard->placeChess(new BlackChess(x, y));
            }
            return ok;
        }

    private:


};

#endif