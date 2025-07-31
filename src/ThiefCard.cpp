#include "../include/ThiefCard.h"
#include "../include/map.h"
#include "../include/monster.h"
#include "../include/hero.h"
#include "../include/dice.h"
#include "../include/game-controller.h"

#include <iostream>
#include <unordered_map>

std::string ThiefCard::get_name() const
{
    return "Thief";
}

std::string ThiefCard::get_description() const
{
    return "Invisible Man moves 1, attacks once.";
}

void ThiefCard::apply(Map& map , std::vector<Monster*>& monsters , std::vector<Hero*>& heroes , Dice& dice , GameController& controller)
{
    auto items = map.get_itemBag().drawRandomItems(2);
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
        std::cout << "Invisible Man is not in the game...\n";
        return;
    }

    //moving one step
    std::string current = invisibleMan->get_currentLocation();
    std::string nearest = map.findNearestHeroLocation(current , heroes);

    if (!nearest.empty() && map.areConnected(current , nearest))
    {
        map.set_characterLocation(invisibleMan->get_name() , nearest);
        invisibleMan->set_location(nearest);
        std::cout << "Invisible Man moved to " << nearest << "\n";
    }else{
        std::cout << "No valid move for Invisible Man.\n";
        return;
    }

    std::vector<DiceFace> faces = dice.rollMultiple(3);
    int strikes = dice.countStrikes(faces);
    int power = dice.countPowers(faces);

    if (strikes > 0)
    {
        bool attacked = false;
        //attacks with hero
        for (Hero* h : heroes)
        {
        if (h->get_location() == invisibleMan->get_currentLocation())
        {
            invisibleMan->attack(*h);
            break;
        }
    }
    if (!attacked)
    {
        std::vector<Villager*> villagersHere = map.getVillagersAt(invisibleMan->get_currentLocation());
        if (!villagersHere.empty())
        {
            map.removeVillager(villagersHere.front());
            controller.increaseTerrorLevel();
            std::cout << "A villager was attacked by Invisible Man! Terror Level is increased.\n";
        }else{
            std::cout << "No one attacks at " << invisibleMan->get_currentLocation() << "\n";
        }
    }
    }
    if (power > 0)
    {
        std::cout << "Invisible Man used power effect...\n";
    }
}
