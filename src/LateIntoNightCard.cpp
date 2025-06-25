#include "../include/LateIntoNightCard.h"
#include "../include/hero.h"
#include <iostream>

std::string LateIntoNightCard::get_name() const 
{
    return "Late into the Night";
}

std::string LateIntoNightCard::get_description() const 
{
    return "current hero receives 2 extra actions!";
}

void LateIntoNightCard::apply(Hero& currentHero , std::vector<Hero*>& , std::vector<Monster*>& , ItemBag& , Map& , bool&) 
{
    currentHero.addExtraActions(2);
    std::cout << currentHero.get_name() << " has 2 extra actions now!" << std::endl;
}
