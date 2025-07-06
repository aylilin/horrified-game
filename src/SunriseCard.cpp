#include "../include/SunriseCard.h"
#include "../include/map.h"
#include "../include/monster.h"
#include "../include/hero.h"
#include "../include/villager.h"
#include "../include/dice.h"
#include "../include/game-controller.h"
#include <iostream>

std::string SunriseCard::get_name() const
{
    return "Sunrise";
}

std::string SunriseCard::get_description() const
{
    return "Dracula moves to Crypt , Invisible Man strikes with 3 dice.";
}

void SunriseCard::apply(Map& map , std::vector<Monster*>& monsters , std::vector<Hero*>& heroes , Dice& dice , GameController& controller)
{
    Monster* InvisibleMan = nullptr;
    Monster* Dracula = nullptr;

    for (Monster* m : monsters)
    {
        if (m->get_name() == "Dracula")
        {
            Dracula = dynamic_cast<Monster*>(m);
        }
            else if (m->get_name() == "Invisible Man")
            {
                InvisibleMan = m;
            }

            if (Dracula)
            {
                Dracula->set_location("Crypt");
                map.placeMonster(Dracula , "Crypt");
                std::cout << "Dracula moved to Crypt.\n";
            }
            
            if (InvisibleMan)
            {
                std::vector<DiceFace> faces = dice.rollMultiple(3);
                std::cout << "Invisible Man rolled 3 dice.\n";

                if (dice.countPowers(faces) > 0)
                {
                    std::cout << "Power triggered for Invisible Man!\n";
                }

                //strike and attack
                int strikes = dice.countStrikes(faces);
                if (strikes > 0)
                {
                    map.monsterStrike(InvisibleMan , strikes , heroes , controller);
                }else{
                    std::cout << "Invisible Man did not strike.\n";
                }
            }

        }
    }
