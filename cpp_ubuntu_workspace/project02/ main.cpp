#include "ChessBoard.hpp"
#include "WhitePlayer.hpp"
#include "BlackPlayer.hpp"
#include "KeyHandle.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    ChessBoard *chessBoard = ChessBoard::getChessBoard();
    chessBoard->show();

    BlackPlayer bPlayer("lisi");
    WhitePlayer wPlayer("zhangsan");
    /* 
    wPlayer.placeChess(5, 7);
    bPlayer.placeChess(5, 3); */

    KeyHandle k;
    
    while (1)
    {
        k.waitPlayerPlaceChess(&bPlayer);
    }
    

    return 0;
}
