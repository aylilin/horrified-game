#include "../include/EgyptianExpert.h"
#include "../include/villager.h"
#include "../include/map.h"
#include "../include/dice.h"

#include <iostream>

std::string EgyptianExpertCard::get_name() const
{
    return "Egyptian Expert";
}

std::string EgyptianExpertCard::get_description() const
{
    return "place Prof. Pearson at Cave. Dracula move 1 step and strikes 2 dice.";
}

void EgyptianExpertCard::apply(Map& map , std::vector<Monster*>& monsters , std::vector<Hero*>& heroes , Dice& dice , GameController& controller)
{
    //add 3 items
    auto items = map.get_itemBag().drawRandomItems(3);
    for (const auto& item : items)
    {
        map.placeItem(item);
    }

    //add villager
    Villager* Pearson = new Villager("Prof. Pearson" , "Museum");
    Pearson->set_location("Cave");
    map.addVillager(Pearson);
    std::cout << "Prof. Pearson appeared at Cave.\n";

    for (Monster* m : monsters)
    {
        if (m->get_name() == "Dracula")
        {
            map.moveMonster(m , 1 , dice);
            auto faces = dice.rollMultiple(2);
            int strikes = dice.countStrikes(faces);
            map.monsterStrike(m , strikes , heroes , controller);
        }
    }
}