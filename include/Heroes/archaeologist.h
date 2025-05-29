#pragma once
#include "hero.h"

class Archaeologist : public Hero
{
public:
    Archaeologist(const std::string& name , const std::string& startLocation);

    void specialAction();
};