#include "Luban.h"

// 继承的构造函数的传参
Luban::Luban(const string &name, int distance, int legLen):
    Hero(name),
    Shooter(distance),
    skin("red")
{
    cout << "name::" << name << " distance::" << distance << " legLen::" << legLen << endl;
    this->legLen = legLen;
    cout << "---------------------------" << endl;
}

Luban::~Luban() 
{
}

void Luban::show() {
    cout << "luban name : " << getName() << endl;
    cout << "luban distance : " << getDistance() << endl;
    cout << "luban leglen : " << legLen << endl;
    cout << "luban skin : " << skin.getSkin() << endl;
}

void Luban::skill() {
    cout << "luban skill" << endl;
}