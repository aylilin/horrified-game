#include "Heroes/Mayor.h"
#include <iostream>

Mayor::Mayor(const std::string& name , const std::string& startLocation)
: Hero(name , 5 , startLocation)
{
    if (name.empty())
    {
        throw std::invalid_argument("Mayor's name could not be empty!");
    }
}

void Mayor::specialAction()
{
    std::cout << name << "has no specialAction!" << std::endl;
}

void Mayor::manageTownResources()
{
    if (remainingActions > 0)
    {
        std::cout << "Mayor manages townresources..." << std::endl;
        remainingActions--;
    }
}