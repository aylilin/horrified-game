#include "../include/FormerEmployerCard.h"
#include "../include/villager.h"
#include "../include/itemBag.h"
#include "../include/invisible-man.h"
#include "../include/dice.h"

#include <iostream>

std::string FormerEmployerCard::get_name() const
{
    return "Former Employer";
}

std::string FormerEmployerCard::get_description() const
{
    return "Add 3 items. Place Dr. Cranly at Laboratory. Strike: Invisible Man then Frenzied Monster";
}

void FormerEmployerCard::apply(Map& map , std::vector<Monster*>& monsters , std::vector<Hero*>& heroes, Dice& dice , GameController& controller)
{
    std::vector<Item> items = map.get_itemBag().drawRandomItems(3);
    for (const auto& item : items)
    {
        map.placeItem(item);
    }

    Villager* cranly = new Villager("Dr. Cranly", "Precinct");
    cranly->set_location("Laboratory");
    map.addVillager(cranly);
    std::cout << "Dr. Cranly appeared at Laboratory.\n";

    Monster* InvisibleMan = nullptr;
    //inbisible man attacks
    for (Monster* m : monsters)
    {
    if (m->get_name() == "Invisible Man")
    {
        InvisibleMan = m;
    }

    if (InvisibleMan)
    {
        map.moveMonster(InvisibleMan , 1 , dice);

        //invisible man attacks
        std::vector<DiceFace> faces = dice.rollMultiple(2);
        int strikes = dice.countStrikes(faces);
        int powers = dice.countPowers(faces);

        map.monsterStrike(InvisibleMan , strikes , heroes , controller);

        if (powers > 0)
        {
            std::cout << "Power triggered for Invisible Man!\n";
        }
    }
}
}
