#ifndef __DISCOUNT_METHOD_H__
#define __DISCOUNT_METHOD_H__

#include "Method.hpp"

class DiscountMethod: public Method {
    public:
        DiscountMethod(float discount): discount(discount) {}

        virtual int calc(int money) 
        {
            return money * discount;
        }
    
    private:
        float discount;
};

#endif