#include "../include/HurryCard.h"
#include "../include/hero.h"
#include "../include/map.h"
#include <iostream>

std::string HurryCard::get_name() const 
{
    return "Hurry";
}

std::string HurryCard::get_description() const 
{
    return "Each hero can move up to two spaces.";
}

void HurryCard::apply(Hero& , std::vector<Hero*>& allHeroes , std::vector<Monster*>& , ItemBag& , Map& map , bool&) {
    for (Hero* hero : allHeroes) 
    {
        std::cout << "\n Hero " << hero->get_name() << "\n";

        for (int step = 1; step <= 2; step++) 
        {
            std::string currentLocation = map.get_characterLocation(hero->get_name());

            std::cout << "Step " << step << " | Current Location " << currentLocation << "\n";
            std::cout << "Enter your desired destination (or '0' to stop) : ";
            std::string target;
            std::getline(std::cin, target);

            if (target == "0") 
            {
                std::cout << "The move was cancelled...\n";
                break;
            }

            if (map.areConnected(currentLocation, target)) 
            {
                map.set_characterLocation(hero->get_name(), target);
                hero->set_location(target);
                std::cout << "Hero was moved to " << target << "\n";
            } else {
                std::cout << "The entered location is not connected. The move failed...\n";
                break;
            }
        }
    }
}
