#include "../include/VisitDetectiveCard.h"
#include "../include/monster.h"
#include "../include/perkCard.h"
#include "../include/map.h"
#include <iostream>

std::string VisitDetectiveCard::get_name() const 
{
    return "Visit from the Detective";
}

std::string VisitDetectiveCard::get_description() const 
{
    return "move the invisible man to your favorite location";
}

void VisitDetectiveCard::apply(Hero& , std::vector<Hero*>& , std::vector<Monster*>& monsters , ItemBag& , Map& map , bool&)
{
    Monster* invisibleMan = nullptr;

    for (Monster* monster : monsters) 
    {
        if (monster->get_name() == "Invisible Man") 
        {
            invisibleMan = monster;
            break;
        }
    }

    if (!invisibleMan) 
    {
        std::cout << "There is no invisibleMan in the game!\n";
        return;
    }

    std::string targetLocation;
    std::cout <<"Enter the name of the location you want to move the Invisible Man to : ";
    std::getline(std::cin, targetLocation);

    map.set_characterLocation("Invisible Man", targetLocation);
    invisibleMan->set_location(targetLocation);

    std::cout << "Invisible Man was moved to " << targetLocation << "\n";
}
