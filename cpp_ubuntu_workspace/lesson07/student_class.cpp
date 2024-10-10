#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

class Student 
{
private:
    string name;
    int age;
    int score;

public:
    Student();
    Student(const string &name, int age, int score);
    void setName(const string &_name);
    void setAge(const int &_age);
    void setScore(const int &_score);

    void playGame(const char *game);
};

Student::Student()
{
    cout << "Student()" << endl;
    name = "";
    age = 0;
    score = 0;
}
Student::Student(const string &name, int age, int score):name(name),age(age),score(score) //初始化列表的形式
{
    cout << "Student::Student(const string &name, int age, int score)" << endl;
#if 0
    this->name = name;
    this->age = age;
    this->score = score;
#endif
}

void Student::setName(const string &_name)
{
    name = _name;
}
void Student::setAge(const int &_age)
{
    age = _age;
}
void Student::setScore(const int &_score)
{
    score = _score;
}

void Student::playGame(const char *game)
{
    // printf("%s play %s\n", pstu->name, game);
    cout << this->name << " play " <<  game << endl;

    // 结构体内函数可以直接访问属性, 谁调用这个函数,属性就是谁的变量
    cout << "name " << name << " age " << age << endl;
}

Student gstu; // 静态区对象

int main(int argc, char const *argv[])
{
    Student stu;//在栈区创建的对象(在函数结束后自动释放)
    static Student stu1;    //静态区对象 (在程序结束后自动释放)

    stu.playGame("King");
    cout << "--------------------------" << endl;

    stu.setName("xiaoming");
    stu.setAge(18);
    stu.setScore(95);
    stu.playGame("King");
    cout << "--------------------------" << endl;

    // Student *pstu 在栈区创建变量
    // new Student 在堆区创建对象(通过new运算符分配内存, 通过delete运算符释放内存)
    Student *pstu = new Student; 
    pstu->setName("lisi");
    delete pstu;

    cout << "--------------------------" << endl;
    Student stu2("xiaoming", 20, 100);
    stu2.playGame("King");
    return 0;
}
