#include "itemBag.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

ItemBag::ItemBag()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    generateRandomItems(60);
}

void ItemBag::generateRandomItems(int count)
{
    static std::vector<std::string> Locations = {"Cave", "Inn", "Theater", "Tower", "Crypt", "Laboratory","Mansion", "Graveyard", "Barn", "Dungeon"};

    for (int i = 0 ; i < count ; i++)
    {
        Item::Type type = static_cast<Item::Type>(std::rand() % 3);
        int power = 1 + std::rand() % 6;
        std::string loc = Locations[std::rand() % Locations.size()];
        items.emplace_back(name, type, power, loc);
    }
}

Item ItemBag::drawRandomItem()
{
    if (items.empty()) {
        throw std::out_of_range("Item bag is empty!");
    }

    int index = std::rand() % items.size();
    Item selected = items[index];
    items.erase(items.begin() + index);
    return selected;
}

bool ItemBag::isEmpty() const 
{
    return items.empty();
}

void ItemBag::returnItem(const Item& item) 
{
    items.push_back(item);
}

void ItemBag::printSummary() const {
    int red = 0, blue = 0, yellow = 0;

    for (const auto& item : items) {
        switch (item.get_type()) {
            case Item::Type::RED: red++; break;
            case Item::Type::BLUE: blue++; break;
            case Item::Type::YELLOW: yellow++; break;
        }
    }

    std::cout << "Item color summary:\n";
    std::cout << "RED: " << red << "\nBLUE: " << blue << "\nYELLOW: " << yellow << "\n";
}
