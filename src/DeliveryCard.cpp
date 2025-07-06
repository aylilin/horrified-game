#include "../include/DeliveryCard.h"
#include "../include/map.h"
#include "../include/monster.h"
#include "../include/hero.h"
#include "../include/villager.h"
#include "../include/dice.h"
#include "../include/game-controller.h"

#include <iostream>

std::string DeliveryCard::get_name() const
{
    return "Delivery";
}

std::string DeliveryCard::get_description() const
{
    return "Invisible Man moves 2 steps, attacks once, and a villager appears.";
}

void DeliveryCard::apply(Map& map , std::vector<Monster*>& monsters , std::vector<Hero*>& heroes , Dice& dice , GameController& controller)
{
    auto items = map.get_itemBag().drawRandomItems(3);
    for (const auto& item : items)
    {
        map.placeItem(item);
    }

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
    map.moveMonster(invisibleMan , 2 , dice);

    std::vector<DiceFace> faces = dice.rollMultiple(3);

    int strikes = dice.countStrikes(faces);
    int powers = dice.countPowers(faces);

    if (strikes > 0)
    {
        map.monsterStrike(invisibleMan , strikes , heroes , controller);
    }

    if (powers > 0)
    {
        std::cout << "Invisible Man's power activated\n";
    }

    Villager* v = new Villager("Unnamed", "Hospital");
    v->set_location(invisibleMan->get_currentLocation());
    map.addVillager(v);

    std::cout << "there is one villager " << invisibleMan->get_currentLocation() << "\n";
}
