#pragma once

#include "monster.h"

#include <map>

class Dracula : public Monster
{
private:
    std::map<std::string , bool> coffins;
    int coffinDestroyed = 0;

public:
    Dracula();

    int getCoffinsDestroyed() const;
    bool isCoffinDestroyed(const std::string& Location) const;

    virtual void useSpecialPower();
    bool checkDefeatConditions() const;

};