#ifndef __GAME_STUDENT_H__
#define __GAME_STUDENT_H__

#include "Observer.hpp"

class GameStudent:public Observer
{
    public:
        GameStudent(Subject *subject):Observer(subject){}
        void update()
        {
            cout << "Stop play game" << endl;
		    cout << subject->getMessage() << endl;
        }
};

#endif