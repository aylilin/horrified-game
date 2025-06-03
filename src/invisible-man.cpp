#include "invisible-man.h"
#include <iostream>

void InvisibleMan::useSpecialPower() 
{
    std::cout << name << " uses STALK UNSEEN!" << std::endl;

}

bool InvisibleMan::checkDefeatConditions() const
{
    return collectedEvidences.size() >= 5;
}