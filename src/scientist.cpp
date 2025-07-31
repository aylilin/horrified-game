#include "scientist.h"
#include <iostream>

Scientist::Scientist(const std::string& playerName , const std::string& startLocation) : Hero(playerName , 4 , startLocation) {}

void Scientist::specialAbility()
{
    std::cout << "Scientist using special ability : Research or healing!\n";
    health++;
    if (health > 4) health = 4;
}