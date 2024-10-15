#ifndef __POWER_ADAPTER_H__
#define __POWER_ADAPTER_H__

#include <iostream>
#include "Plug.hpp"
#include "Target.hpp"

using namespace std;

class PowerAdapter: public Target
{
    public:

        void setPlug(Plug *plug)
        {
            this->plug = plug;
        }

        virtual int getOutput5V(void)
        {
            int v = plug->outputV();
            int div = v / 5;

            cout << v << " change " << v/div << endl;
            return v / div;
        }

    private:
        Plug *plug;
        
};

#endif