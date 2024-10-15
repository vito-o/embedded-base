#include "TeacherSubject.hpp"
#include "SleepStudent.hpp"
#include "GameStudent.hpp"

int main(int argc, char const *argv[])
{
    TeacherSubject *teacherSubject = new TeacherSubject;
    teacherSubject->add(new SleepStudent(teacherSubject));
    teacherSubject->add(new GameStudent(teacherSubject));
    teacherSubject->change("Go To class");

    return 0;
}
