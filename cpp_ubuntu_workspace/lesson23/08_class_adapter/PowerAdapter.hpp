#ifndef __POWER_ADAPTER_H__
#define __POWER_ADAPTER_H__

#include <iostream>
#include "ChinaPlug.hpp"
#include "Target.hpp"

using namespace std;

class PowerAdapter: public Target, public ChinaPlug
{
    public:

        virtual int getOutput5V(void)
        {
            int v = outputV();
            int div = v / 5;

            cout << v << " change " << v/div << endl;
            return v / div;
        }
        
};

#endif