#include "../include/FormOfTheBatCard.h"
#include "../include/map.h"
#include "../include/monster.h"
#include "../include/hero.h"
#include "../include/dice.h"
#include "../include/villager.h"
#include "../include/game-controller.h"

#include <iostream>

std::string FormOfTheBatCard::get_name() const
{
    return "Form of the Bat";
}

std::string FormOfTheBatCard::get_description() const
{
    return "Dracula moves 2 steps, attacks once, and a villager appears.";
}

void FormOfTheBatCard::apply(Map& map , std::vector<Monster*>& monsters , std::vector<Hero*>& heroes , Dice& dice , GameController& controller)
{
    //add items
    auto items = map.get_itemBag().drawRandomItems(2);
    for (const auto& item : items)
    {
        map.placeItem(item);
    }

    Monster* dracula = nullptr;
    for (Monster* m : monsters)
    {
        if (m->get_name() == "Dracula")
        {
            dracula = m;
            break;
        }
    }

    if (!dracula)
    {
        std::cout << "Dracula is not in the game...\n";
        return;
    }

        std::string current = dracula->get_currentLocation();
        std::cout << "Dracula's current location: " << current << "\n";

        auto neighbors = map.getConnections(current);
        if (neighbors.empty())
        {
            std::cout << "Dracula has no connected locations.\n";
            return;
        }

        std::string destination;
        std::cout << "Enter Dracula's destination (connected): ";
        std::getline(std::cin , destination);

        if (!map.areConnected(current , destination))
        {
            std::cout << "Invalid move.\n";
            return;
        }

        //move
        map.set_characterLocation(dracula->get_name() , destination);
        dracula->set_location(destination);
        std::cout << "Dracula moved to " << destination << "\n";
        
        //roll dice
        std::vector<DiceFace> faces = dice.rollMultiple(2);
        int strikes = dice.countStrikes(faces);
        int powers = dice.countPowers(faces);

        std::vector<Hero*> targets = map.getHeroesAt(dracula->get_currentLocation());
        std::vector<Villager*> villagers = map.getVillagersAt(dracula->get_currentLocation());

        //apply strike if possible 
        if (strikes > 0 && (!targets.empty() || !villagers.empty()))
        {
            std::cout << "Dracula attacks with stregth: " << strikes << "\n";
            if (!targets.empty())
            {
                targets[0]->receiveDamage(strikes);
            }else if (!villagers.empty())
            {
                Villager* victim = villagers[0];
                std::cout << "villager " << victim->get_name() << " was defeated!\n";
                map.removeVillager(victim);
                controller.increaseTerrorLevel();
            }
        }
        else{
            std::cout << "no one to attack.\n";
        }

        if (powers > 0)
        {
            Villager* v = new Villager("Unnamed" , "Hospital");
            v->set_location(dracula->get_currentLocation());
            map.addVillager(v);
            std::cout << "A villager appeared at " << dracula->get_currentLocation() << "\n";
        }
    }
