#ifndef __OBSERVER_H__
#define __OBSERVER_H__

// #include "Subject.hpp"

class Subject;

class Observer
{
    public:
        Observer(Subject *subject): subject(subject) {}
        virtual void update(void) = 0;

    protected:
        Subject *subject;
};

#endif