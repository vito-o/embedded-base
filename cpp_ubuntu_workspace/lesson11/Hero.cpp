#include "Hero.h"

Hero::Hero(const string &name)
{
    this->name = name;
    cout << "Hero::Hero:" << this->name << endl;
}

Hero::~Hero() 
{
    
}

void Hero::skill()
{

}

string Hero::getName()
{
    return name;
}