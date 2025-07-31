#include "../include/TheInnocent.h"
#include "../include/villager.h"
#include "../include/map.h"
#include "../include/dice.h"
#include "../include/monster.h"
#include "../include/hero.h"

#include <iostream>

std::string TheInnocentCard::get_name() const
{
    return "The Innocent";
}

std::string TheInnocentCard::get_description() const
{
    return "Maria appears at Barn.Dracula moves 1 step and strikes if anyone is there.";
}

void TheInnocentCard::apply(Map& map , std::vector<Monster*>& monsters , std::vector<Hero*>& heroes , Dice& dice , GameController& controller)
{
    //add items
    auto items = map.get_itemBag().drawRandomItems(3);
    for (const auto& item : items)
    {
        map.placeItem(item);
    }

    Villager* Maria = new Villager("Maria" , "Barn");
    Maria->set_location("Barn");
    map.addVillager(Maria);
    std::cout << "Maria has appeared at Barn.\n";

    //find Dracula
    Monster* Dracula = nullptr;
    for (Monster* m : monsters)
    {
        if (m->get_name() == "Dracula")
        {
            Dracula = m;
            break;
        }
    }

    if (!Dracula)
    {
        std::cout << "Dracula is not in the game.\n";
        return;
    }

    //move 1 step
    map.moveMonster(Dracula , 1 , dice);
    std::cout << "Dracula moved one step.\n";

    //2 dice for attack
    std::vector<DiceFace> faces = dice.rollMultiple(2);
    int strikes = dice.countStrikes(faces);

    map.monsterStrike(Dracula , strikes , heroes , controller);
}