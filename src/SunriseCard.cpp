#include "../include/SunriseCard.h"
#include "../include/map.h"
#include "../include/monster.h"
#include "../include/hero.h"
#include "../include/villager.h"
#include "../include/dice.h"
#include <iostream>

std::string SunriseCard::get_name() const
{
    return "Sunrise";
}

std::string SunriseCard::get_description() const
{
    return "Dracula moves 1, attacks 1, and a villager appears.";
}

void SunriseCard::apply(Map& map , std::vector<Monster*>& monsters , std::vector<Hero*>& heroes , Dice&) {
    Monster* dracula = nullptr;
    for (Monster* m : monsters)
    {
        if (m->get_name() == "Dracula")
        {
            dracula = m;
            break;
        }
    }

    if (!dracula) return;

    std::string current = dracula->get_currentLocation();
    std::string next;
    std::cout << "[Dracula] current locaation : " << current << "\n";
    std::cout << "Enter the next move : ";
    std::getline(std::cin, next);

    if (next != "" && map.areConnected(current, next)) {
        map.set_characterLocation(dracula->get_name(), next);
        dracula->set_location(next);
        std::cout << "Dracula moved to " << next << "\n";
    }

    //attack
    for (Hero* h : heroes)
    {
        if (h->get_location() == dracula->get_currentLocation())
        {
            dracula->attack(*h);
        }
    }

    Villager* v = new Villager("Unnamed", "Hospital");
    v->set_location(dracula->get_currentLocation());

    map.addVillager(v);
    std::cout << "one villager is in Dracula's location.\n";
}
