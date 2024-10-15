#ifndef __SLEEP_STUDENT_H__
#define __SLEEP_STUDENT_H__

#include "Observer.hpp"

class SleepStudent:public Observer
{
    public:
        SleepStudent(Subject *subject):Observer(subject){}
        void update()
        {
            cout << "Stop sleep" << endl;
            cout << subject->getMessage() << endl;	
        }
};

#endif