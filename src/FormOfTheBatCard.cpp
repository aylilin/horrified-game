#include "../include/FormOfTheBatCard.h"
#include "../include/map.h"
#include "../include/monster.h"
#include "../include/hero.h"
#include "../include/dice.h"
#include "../include/villager.h"
#include <iostream>

std::string FormOfTheBatCard::get_name() const
{
    return "Form of the Bat";
}

std::string FormOfTheBatCard::get_description() const
{
    return "Dracula moves 2 steps, attacks once, and a villager appears.";
}

void FormOfTheBatCard::apply(Map& map , std::vector<Monster*>& monsters , std::vector<Hero*>& heroes , Dice&)
{
    Monster* dracula = nullptr;
    for (Monster* m : monsters)
    {
        if (m->get_name() == "Dracula")
        {
            dracula = m;
            break;
        }
    }

    if (!dracula)
    {
        std::cout << "Dracula is not in the game...\n";
        return;
    }

    for (int i = 0; i < 2; ++i)
    {
        std::string current = dracula->get_currentLocation();
        std::string next;
        std::cout << "[Dracula] current location : " << current << "\n";
        std::cout << "move " << i + 1 << " --> enter destination : ";
        std::getline(std::cin, next);

        if (map.areConnected(current, next))
        {
            map.set_characterLocation(dracula->get_name(), next);
            dracula->set_location(next);
        } else {
            std::cout << "invalid location.move canceled...\n";
            break;
        }
    }

    //attack with hero
    for (Hero* h : heroes)
    {
        if (h->get_location() == dracula->get_currentLocation())
        {
            dracula->attack(*h);
            break;
        }
    }

    Villager* v = new Villager("Unnamed", "Hospital");

    v->set_location(dracula->get_currentLocation());

    map.addVillager(v); 
    std::cout << "A villager appeared at this location." << dracula->get_currentLocation() << "\n";
}
