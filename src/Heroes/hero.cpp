#include "Heroes/hero.h"
#include <iostream>
#include <stdexcept>

Hero::Hero(const std::string& name , int actions , std::string& startLocation) 
: name(name) , actions(actions) , remainingActions(actions) , currentLocation(startLocation) 
{
    if (actions <= 0)
    {
        throw std::invalid_argument("number of actions must be positive!");
    }

    if (name.empty())
    {
        throw std::invalid_argument("hero's name could not be empty!");
    }
}

void Hero::move(const std::string& newLocation)
{
    if (remainingActions > 0)
    {
        currentLocation = newLocation;
        remainingActions--;
        std::cout << name  << "moved to " << newLocation << std::endl;
    }
}