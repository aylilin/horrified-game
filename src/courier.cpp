#include "courier.h"
#include <iostream>


Courier::Courier(const std::string& name , const std::string& startLocation) : Hero(name , 4 , startLocation) {}

void Courier::specialAbility()
{
    std::cout << "Courier using special ability : fast movement or item delivery!\n";
    extraActions ++;
}