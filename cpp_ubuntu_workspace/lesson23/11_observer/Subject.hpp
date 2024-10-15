#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include <list>
#include <iostream>
#include "Observer.hpp"

using namespace std;

class Subject
{
    public:
        void add(Observer *observer)
        {
            observerList.push_back(observer);
        }

        void remove(Observer *observer)
        {
            observerList.remove(observer);
        }

        void notify(void)
        {
            for(Observer *obj : observerList) {
                obj->update();
            }
        }

        string getMessage(void) const 
        {
            return message;
        }

        void setMessage(const string &message)
        {
            this->message = message;
        }

    private:
        string message;
	    list<Observer *> observerList;
};

#endif