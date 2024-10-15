#include "Market.hpp"
#include "VipMethod.hpp"
#include "DiscountMethod.hpp"

int main(int argc, char const *argv[])
{
    VipMethod *vipMethod = new VipMethod(100);
    Market *market = new Market(vipMethod);

    DiscountMethod *discountMethod = new DiscountMethod((float)0.8);
    Market *market1 = new Market(discountMethod);

    market->calcContext(1000);
    market1->calcContext(1000);

    return 0;
}
