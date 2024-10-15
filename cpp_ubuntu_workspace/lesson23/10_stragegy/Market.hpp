#ifndef __MARKET_H__
#define __MARKET_H__

#include <iostream>
#include "Method.hpp"

using namespace std;

class Market
{
    public:
        Market(Method *method): method(method) {}

        void calcContext(int money)
        {
            cout << "Money: " << method->calc(money) << endl;
        }

    private:
        Method *method;

};

#endif