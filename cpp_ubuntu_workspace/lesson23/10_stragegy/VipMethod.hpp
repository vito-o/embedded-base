#ifndef __VIP_METHOD_H__
#define __VIP_METHOD_H__

#include "Method.hpp"

class VipMethod: public Method {
    public:
        VipMethod(int adjust): adjust(adjust) {}

        virtual int calc(int money) 
        {
            if (money - adjust > 0) {
                money = money - adjust;
            }
            return money;
        }
    
    private:
        int adjust;

};

#endif