#ifndef __TEACHER_SUBJECT_H__
#define __TEACHER_SUBJECT_H__

#include "Subject.hpp"

class TeacherSubject: public Subject
{
    public:
        void change(const string &message)
        {
            setMessage(message);
			notify();
        }
};

#endif