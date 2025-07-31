#pragma once

#include "hero.h"
#include <string>

class Scientist : public Hero
{
public:
    Scientist(const std::string& playerName , const std::string& startLocation);
    void specialAbility() override;
};