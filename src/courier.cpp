#include "courier.h"
#include <iostream>

Courier::Courier(const std::string& playerName , const std::string& startLocation) : Hero(playerName , 4 , startLocation) {}

void Courier::specialAbility()
{
    std::cout << "Courier using special ability : fast movement or item delivery!\n";
    extraActions ++;
}