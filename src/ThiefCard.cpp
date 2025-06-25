#include "../include/ThiefCard.h"
#include "../include/map.h"
#include "../include/monster.h"
#include "../include/hero.h"
#include "../include/dice.h"
#include <iostream>

std::string ThiefCard::get_name() const
{
    return "Thief";
}

std::string ThiefCard::get_description() const
{
    return "Invisible Man moves 1, attacks once.";
}

void ThiefCard::apply(Map& map , std::vector<Monster*>& monsters , std::vector<Hero*>& heroes , Dice&)
{
    Monster* invisibleMan = nullptr;
    for (Monster* m : monsters)
    {
        if (m->get_name() == "Invisible Man")
        {
            invisibleMan = m;
            break;
        }
    }

    if (!invisibleMan)
    {
        std::cout << "Invisible Man is not in the game...\n";
        return;
    }

    //moving one step
    std::string current = invisibleMan->get_currentLocation();
    std::string next;
    std::cout << "[Invisible Man] current location : " << current << "\n";
    std::cout << "enter distination : ";
    std::getline(std::cin, next);

    if (map.areConnected(current, next))
    {
        map.set_characterLocation(invisibleMan->get_name(), next);
        invisibleMan->set_location(next);
        std::cout << "Invisible man moved to " << next << "\n";
    } else {
        std::cout << "invalid move...\n";
        return;
    }

    //attack with hero
    for (Hero* h : heroes)
    {
        if (h->get_location() == invisibleMan->get_currentLocation())
        {
            invisibleMan->attack(*h);
            break;
        }
    }
}
