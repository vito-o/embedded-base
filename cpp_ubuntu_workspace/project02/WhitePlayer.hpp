#ifndef __WHITE_PLAYER_H__
#define __WHITE_PLAYER_H__

#include "Player.hpp"
#include "ChessBoard.hpp"
#include "WhiteChess.hpp"

class WhitePlayer: public Player
{
    public:
        WhitePlayer(const string &name):Player(name, "white") {}

        virtual bool placeChess(int x, int y)
        {
            ChessBoard *chessBoard = ChessBoard::getChessBoard();

            bool ok = chessBoard->isVaildPosition(x, y);
            if (ok)
            {
                chessBoard->placeChess(new WhiteChess(x, y));
            }
            return ok;
        }

    private:


};

#endif