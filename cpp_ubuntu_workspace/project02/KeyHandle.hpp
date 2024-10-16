#ifndef __KEY_HANDLE_H__
#define __KEY_HANDLE_H__

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "Cursor.hpp"

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
        }
        ~KeyHandle() 
        {
            struct termios attr;
            tcgetattr(0, &attr); //获取属性
            attr.c_lflag |= (ICANON | ECHO);    //回车确认和回显
            tcsetattr(0, TCSANOW, &attr);
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
};

#endif