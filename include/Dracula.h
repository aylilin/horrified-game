#pragma once

#include "monster.h"
#include <map>

class Dracula : public Monster
{
private:
    std::map<std::string , bool> coffins;
    int coffinDestroyed;

public:
    Dracula();

    int getCoffinsDestroyed() const;
    bool isCoffinDestroyed(const std::string& Location) const;

    void destroyCoffin(const std::string& Location);
    void useSpecialPower() override;
    bool checkDefeatConditions() const override;

};