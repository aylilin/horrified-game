#include "monster.h"
#include <iostream>

Monster::Monster(const std::string& name)
: name(name) , isDead(false) , health(100) {}

void Monster::move(const std::string& newLocation)
{
    currentLocation = newLocation;
    std::cout << name << " moved to " << newLocation << std::endl;
}

void Monster::attack()
{
    std::cout << name << " attacks..." << std::endl;
}

std::string Monster::get_name() const
{
    return name;
}

std::string Monster::get_currentLocation() const
{
    return currentLocation;
}

bool Monster::get_isDead() const
{
    return isDead;
}

