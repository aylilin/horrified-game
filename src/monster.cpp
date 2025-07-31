#include "../include/hero.h"
#include "../include/itemBag.h"
#include "../include/monster.h"

#include <iostream>

Monster::Monster(const std::string& name)
: name(name) , currentLocation("") , health(3) , isDead(false) {}

void Monster::move(const std::string& newLocation)
{
    currentLocation = newLocation;
    std::cout << name << "moved to " << newLocation << "\n";
}

void Monster::attack(Hero& target)
{
    std::cout << name << " attacked to " << target.get_name() << "\n";
    target.receiveDamage(1);  // attack power = 1 
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

void Monster::set_location(const std::string& newLoc)
{
    currentLocation = newLoc;
}