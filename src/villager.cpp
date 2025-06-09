#include "../include/villager.h"

Villager::Villager(const std::string& name , const std::string& startLocation , const std::string& safeLocation)
    : name(name) , currentLocation(startLocation) ,
    safeLocation(safeLocation) , alive(true) {}

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
