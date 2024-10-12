#include "Houyi.h"

// 继承的构造函数的传参
Houyi::Houyi(const string &name, int distance, int legLen):
    Hero(name),
    Shooter(distance),
    skin("red")
{
    cout << "name::" << name << " distance::" << distance << " legLen::" << legLen << endl;
    this->legLen = legLen;
    cout << "---------------------------" << endl;
}

Houyi::~Houyi() 
{
}

void Houyi::show() {
    cout << "Houyi name : " << getName() << endl;
    cout << "Houyi distance : " << getDistance() << endl;
    cout << "Houyi leglen : " << legLen << endl;
    cout << "Houyi skin : " << skin.getSkin() << endl;
}

void Houyi::skill() {
    cout << "houyi skill" << endl;
}