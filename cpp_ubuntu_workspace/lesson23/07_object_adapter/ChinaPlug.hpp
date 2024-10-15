#ifndef __CHINA_PLUG_H__
#define __CHINA_PLUG_H__

#include "Plug.hpp"

class ChinaPlug: public Plug
{
    public:
        virtual int outputV(void) 
        {
            return 220;
        }
};

#endif