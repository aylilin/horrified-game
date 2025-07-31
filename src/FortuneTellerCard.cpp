#include "../include/FortuneTellerCard.h"
#include "../include/villager.h"
#include "../include/itemBag.h"
#include "../include/game-controller.h"

#include <iostream>

std::string FortuneTellerCard::get_name() const
{
    return "Fortune Teller";
}

std::string FortuneTellerCard::get_description() const
{
    return "Add 3 items. Place Maleva at Camp. Strike: 1 move + 2 dice (Frenzied Monster)";
}

void FortuneTellerCard::apply(Map& map , std::vector<Monster*>& monsters , std::vector<Hero*>& , Dice& dice , GameController& controller)
{
    std::vector<Item> items = map.get_itemBag().drawRandomItems(3);
    for (const auto& item : items)
    {
        map.placeItem(item);
    }

    Villager* maleva = new Villager("Maleva", "Shop"); // safeLocation = Shop
    maleva->set_location("Camp");
    map.addVillager(maleva);
    std::cout << "Maleva appeared at Camp.\n";
}
