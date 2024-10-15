#ifndef __PROXY_H__
#define __PROXY_H__

#include "Girl.hpp"

class Proxy 
{
    public:
        void setMarryGirl(Girl *girl)
        {
            this->girl = girl;
        }

        void marry(int money) 
        {
            if (money < 100) {
                cout << "no money no marry" << endl;
                return;
            }  
            girl->marry(money);
        }

    private:
       Girl *girl; 
};

#endif
