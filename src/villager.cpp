#include "../include/villager.h"

Villager::Villager(const std::string& name , const std::string& safeLocation)
    : name(name) , safeLocation(safeLocation) , currentLocation("") , guided(false){}

std::string Villager::get_name() const
{
    return name;
}

std::string Villager::get_currentLocation() const
{
    return currentLocation;
}

std::string Villager::get_safeLocation() const
{
    return safeLocation;
}

void Villager::set_location(const std::string& newLoc)
{
    currentLocation = newLoc;
}

bool Villager::isGuided() const
{
    return guided;
}

void Villager::set_guided(bool val)
{
    guided = val;
}

bool Villager::isAlive() const
{
    return alive;
}

void Villager::kill()
{
    alive = false;
}

bool Villager::isSafeLocation() const
{
    return currentLocation == safeLocation;
}
