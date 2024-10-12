#include "Shooter.h"

Shooter::Shooter(int distance)
{
    this->distance = distance;
    cout << "Shooter::Shooter:" << this->distance << endl;
}

Shooter::~Shooter() 
{
}


int Shooter::getDistance()
{
    return distance;
}