#include <iostream>
#include "space.h"

using namespace A_Space;
using namespace B_Space;

int main(int argc, char const *argv[])
{
    
    std::cout << A_Space::calc(1, 2) << std::endl;
    std::cout << B_Space::calc(4, 2) << std::endl;

    return 0;
}

