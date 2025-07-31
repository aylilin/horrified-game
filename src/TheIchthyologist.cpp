#include "../include/TheIchthyologist.h"
#include "../include/villager.h"
#include "../include/map.h"

#include <iostream>

std::string TheIchthyologistCard::get_name() const
{
    return "The Ichthyologist";
}

std::string TheIchthyologistCard::get_description() const
{
    return "Place Dr. Read at Institute.";
}

void TheIchthyologistCard::apply(Map& map , std::vector<Monster*>& monsters , std::vector<Hero*>& heroes , Dice& dice , GameController& controller)
{
    //add 3 items
    auto items = map.get_itemBag().drawRandomItems(3);
    for (const auto& item : items)
    {
        map.placeItem(item);
    }

    //add villager
    Villager* Read = new Villager("Dr. Read" , "Camp");
    Read->set_location("Institute");
    map.addVillager(Read);
    std::cout << "Dr. Read appeared at Institute.\n";

    for (Monster* m : monsters)
    {
        if (m->get_name() == "Invisible Man")
        {
            map.moveMonster(m , 1 , dice);
            auto faces = dice.rollMultiple(2);
            int strikes = dice.countStrikes(faces);
            map.monsterStrike(m , strikes , heroes , controller);
            break;
        }
    }
}