#pragma once

#include "hero.h"
#include <string>

class Courier : public Hero
{
public:
    Courier(const std::string& playerName , const std::string& startLocation);
    void specialAbility() override;
};