#pragma once
#include "hero.h"

class Mayor : public Hero
{
public:
    Mayor(const std::string& name , const std::string& startLocation);

    void specialAbility() override;
    void manageTownResources();
};