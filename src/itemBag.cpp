#include "itemBag.h"
#include "hero.h"
#include "monster.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <random>

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
        items.emplace_back("item name" , type , power , loc);
    }
}

std::vector<Item> ItemBag::drawRandomItems(int count)
{
    std::vector<Item> selected;

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(items.begin(), items.end(), g);

    for (int i = 0; i < count && !items.empty(); ++i)
    {
        selected.push_back(items.back());
        items.pop_back();
    }

    return selected;
}

bool ItemBag::isEmpty() const 
{
    return items.empty();
}

bool ItemBag::transferItemToHero(const std::string& location, Hero& hero)
{
    auto it = std::find_if(items.begin() , items.end() , [&](const Item& item) 
    {
        return item.get_location() == location;
    });

    if (it != items.end())
    {
        hero.addItem(*it);
        items.erase(it);
        return true;
    }
    return false;
}

void ItemBag::addItem(const Item& item)
{
    items.push_back(item);
}

void ItemBag::returnItem(const Item& item) 
{
    items.push_back(item);
}

void ItemBag::loadFromDefinitions()
{
    items.clear();

    std::vector<std::string> locations = 
    {
        "Docks", "Laboratory", "Institute", "Theatre", "Museum", "Graveyard",
        "Cave", "Tower", "Barn", "Crypt", "Dungeon", "Precinct"
    };

    for (int i = 0; i < 20; ++i)
    {
        items.emplace_back("Item", Item::Type::RED, rand() % 3 + 1, locations[rand() % locations.size()]);
        items.emplace_back("Item", Item::Type::BLUE, rand() % 3 + 1, locations[rand() % locations.size()]);
        items.emplace_back("Item", Item::Type::YELLOW, rand() % 3 + 1, locations[rand() % locations.size()]);
    }
}

void ItemBag::printSummary() const 
{
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
