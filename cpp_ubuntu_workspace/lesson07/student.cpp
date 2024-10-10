#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;
// c++ 对struct结构体进行了增强
struct student 
{
    string name;
    int age;
    int score;
    void playGame(struct student *pstu, const char *game);
};

void student::playGame(struct student *pstu, const char *game)
{
    // printf("%s play %s\n", pstu->name, game);
    cout << pstu->name << " play " <<  game << endl;

    // 结构体内函数可以直接访问属性, 谁调用这个函数,属性就是谁的变量
    cout << "name " << name << " age " << age << endl;
}

int main(int argc, char const *argv[])
{
    // c++对结构体变量初始化时候,可以省略struct
    // struct student stu;
    student stu;

    stu.name = "xiaoming";
    stu.age = 18;
    stu.score = 95;

    stu.playGame(&stu, "King");
    
    return 0;
}
