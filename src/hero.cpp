#include "../include/hero.h"
#include <iostream>
#include <stdexcept>

Hero::Hero(const std::string& name , int actions , const std::string& startLocation) 
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
    if (remainingActions <= 0)
    {
        throw std::runtime_error("there is not enough action...");
    }

    if (newLocation.empty())
    {
        throw std::invalid_argument("location is not valid...");
    }
    
    currentLocation = newLocation;
    remainingActions--;
    std::cout << name  << " moved to " << newLocation << std::endl;
}

void Hero::addExtraActions(int count) 
{
    extraActions += count;
}

void Hero::resetActions() {
    extraActions = 0;
}

void Hero::addItem(const Item& item)
{
    inventory.push_back(item);
}

void Hero::set_location(const std::string& newLocation) 
{
    currentLocation = newLocation;
}

void Hero::receiveDamage(int amount)
{
    health -= amount;
    if (health < 0) health = 0;
    std::cout << name << "Damaged....(health : " << health << ")\n";
}

int Hero::get_health() const
{
    return health;
}

bool Hero::isAlive() const
{
    return health > 0;
}

std::string Hero::get_location() const
{
    return currentLocation;
}
