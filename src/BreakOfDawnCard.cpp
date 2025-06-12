#include "../include/BreakOfDawnCard.h"
#include "../include/itemBag.h"
#include "../include/item.h"
#include "../include/map.h"
#include <iostream>

std::string BreakOfDawnCard::get_name() const 
{
    return "Break of Dawn";
}

std::string BreakOfDawnCard::get_description() const 
{
    return "The monster phase is passed. 2 items are placed on the map.";
}

void BreakOfDawnCard::apply(Hero& , std::vector<Hero*>& , std::vector<Monster*>& , ItemBag& bag , Map& map , bool& skipMonsterPhase) 
{
    skipMonsterPhase = true;
    std::cout << "The monster phase was passed this turn.\n";

    int placed = 0;
    while (placed < 2 && !bag.isEmpty()) 
    {
        std::vector<Item> items = bag.drawRandomItems(3); 

        for (const auto& item : items)
        {
        bag.addItem(item);
        }
        
        placed++;
    }

    if (placed < 2) 
    {
        std::cout << "The item bag had less than 2 items...\n";
    }
}
