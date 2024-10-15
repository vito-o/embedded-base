#ifndef __PHONE_HEAD_H__
#define __PHONE_HEAD_H__

class AbstractPhone
{
    public:
        virtual void call(void) = 0;
        virtual void message(void) = 0;
};

#endif