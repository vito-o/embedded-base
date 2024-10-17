#ifndef __KEY_HANDLE_H__
#define __KEY_HANDLE_H__

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "Cursor.hpp"
#include <map>
#include "Player.hpp"

#define PLACE_CHESS_KEY ' '

using namespace std;

class KeyHandle
{
    public:
        KeyHandle() 
        {
            struct termios attr;
            tcgetattr(0, &attr); //获取属性
            attr.c_lflag &= ~(ICANON | ECHO);   //关闭回车确认和回显
            tcsetattr(0, TCSANOW, &attr);

            auto handleUp    = std::bind(&Cursor::move, &cursor, Cursor::UP);
            auto handleDown  = std::bind(&Cursor::move, &cursor, Cursor::DOWN);
            auto handleLeft  = std::bind(&Cursor::move, &cursor, Cursor::LEFT);
            auto handleRight = std::bind(&Cursor::move, &cursor, Cursor::RIGHT);

            keyMap.insert(pair<char, function<void(void)>>('w', handleUp));
            keyMap.insert(pair<char, function<void(void)>>('W', handleUp));

            keyMap.insert(pair<char, function<void(void)>>('s', handleDown));
            keyMap.insert(pair<char, function<void(void)>>('S', handleDown));

            keyMap.insert(pair<char, function<void(void)>>('a', handleLeft));
            keyMap.insert(pair<char, function<void(void)>>('A', handleLeft));

            keyMap.insert(pair<char, function<void(void)>>('d', handleRight));
            keyMap.insert(pair<char, function<void(void)>>('D', handleRight));
        }
        ~KeyHandle() 
        {
            struct termios attr;
            tcgetattr(0, &attr); //获取属性
            attr.c_lflag |= (ICANON | ECHO);    //回车确认和回显
            tcsetattr(0, TCSANOW, &attr);
        }

        void waitPlayerPlaceChess(Player *player)
        {
            bool ok = false;
            do {
                int ch = getchar();
                if (ch == PLACE_CHESS_KEY) {
                    ok = player->placeChess(cursor.getX(), cursor.getY());
                } else {
                    auto it = keyMap.find(ch);
                    if (it == keyMap.end()) {
                        continue;
                    }
                    auto handle = it->second;
                    handle();
                }

            } while (!ok);
            
        }

        void waitPlaceChess(void)
        {
            int ch;

            while (1)
            {
                ch = getchar();

                switch (ch)
                {
                case 'a':
                case 'A':
                    // printf("left\n");
                    cursor.move(Cursor::LEFT);
                    break;

                case 'd':
                case 'D':
                    // printf("right\n");
                    cursor.move(Cursor::RIGHT);
                    break;

                case 'w':
                case 'W':
                    // printf("top\n");
                    cursor.move(Cursor::UP);
                    break;
                    
                case 's':
                case 'S':
                    // printf("bottom\n");
                    cursor.move(Cursor::DOWN);
                    break;

                case ' ':
                    printf("space\n");
                    break;
                }
            }
            
        }

    private:
        Cursor cursor;
        map<char, function<void(void)>> keyMap;
};

#endif