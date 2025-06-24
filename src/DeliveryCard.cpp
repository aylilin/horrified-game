#include "../include/DeliveryCard.h"
#include "../include/map.h"
#include "../include/monster.h"
#include "../include/hero.h"
#include "../include/villager.h"
#include "../include/dice.h"
#include <iostream>

std::string DeliveryCard::get_name() const
{
    return "Delivery";
}

std::string DeliveryCard::get_description() const
{
    return "Invisible Man moves 2 steps, attacks once, and a villager appears.";
}

void DeliveryCard::apply(Map& map , std::vector<Monster*>& monsters , std::vector<Hero*>& heroes , Dice&)
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
        std::cout << "Invisible Man is not in the game\n";
        return;
    }

    //moving 2 steps
    for (int i = 0; i < 2; ++i)
    {
        std::string current = invisibleMan->get_currentLocation();
        std::string next;
        std::cout << "[Invisible Man] current location : " << current << "\n";
        std::cout << "move " << i + 1 << " enter distination : ";
        std::getline(std::cin, next);

        if (map.areConnected(current, next))
        {
            map.set_characterLocation(invisibleMan->get_name(), next);
            invisibleMan->set_location(next);
        } else {
            std::cout << "invalid move...\n";
            break;
        }
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

    Villager* v = new Villager("Unnamed", "Hospital");
    v->set_location(invisibleMan->get_currentLocation());
    map.addVillager(v);

    std::cout << "there is one villager " << invisibleMan->get_currentLocation() << "\n";
}
