#include "../include/HurriedAssistantCard.h"
#include "../include/villager.h"
#include "../include/map.h"
#include "../include/dice.h"

#include <iostream>

std::string HurriedAssistantCard::get_name() const
{
    return "Hurried Assistant";
}

std::string HurriedAssistantCard::get_description() const
{
    return "Fritz appears at Tower. Dracula moves 2 steps and strikes if present";
}

void HurriedAssistantCard::apply(Map& map , std::vector<Monster*>& monsters , std::vector<Hero*>& heroes , Dice& dice , GameController& controller)
{
    std::vector<Item> items = map.get_itemBag().drawRandomItems(3);
    for (const auto& item : items)
    {
        map.placeItem(item);
    }

    Villager* fritz = new Villager("Fritz" , "Institute"); //safe location for fritz
    fritz->set_location("Tower");
    map.addVillager(fritz);
    std::cout << "fritz has appeared at Tower.\n";

    Monster* Dracula = nullptr;

    for (Monster* m : monsters)
    {
        if (m->get_name() == "Dracula")
        {
            Monster* Dracula = dynamic_cast<Monster*>(m);
            break;
        }
    }
            if (!Dracula)
            {
                std::cout << "Dracula is not present in the game!\n";
                return;
            }

            //move 2 steps
            map.moveMonster(Dracula , 2 , dice);
            std::cout << "Dracula moved 2 steps.\n";

            //4 dice and attack
            std::vector<DiceFace> faces = dice.rollMultiple(3);
            int strikes = dice.countStrikes(faces);

            map.monsterStrike(Dracula , strikes , heroes , controller);
        }