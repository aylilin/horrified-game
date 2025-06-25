#include "../include/OverstockCard.h"
#include "../include/hero.h"
#include "../include/itemBag.h"
#include <iostream>

std::string OverstockCard::get_name() const 
{
    return "Overstock";
}

std::string OverstockCard::get_description() const 
{
    return "Each hero receives one item from the ItemBag.";
}

void OverstockCard::apply(Hero&, std::vector<Hero*>& allHeroes, std::vector<Monster*>&, ItemBag& bag, Map&, bool&)
{
    for (Hero* hero : allHeroes) {
        if (!bag.isEmpty()) {
            std::vector<Item> items = bag.drawRandomItems(1);
            if (!items.empty()) {
                Item item = items[0];
                hero->addItem(item);
                std::cout << hero->get_name() << " received an item: " << item.toString() << "\n";
            }
        } else {
            std::cout << "Item bag is empty! " << hero->get_name() << " didn't receive any item.\n";
        }
    }
}
