#pragma once
#include <vector>
#include <string>

#include "item.h"

class Hero;
class map;

class ItemBag
{
private:
    std::vector<Item> items;

public:
    ItemBag();
    
    void generateRandomItems(int count);
    bool isEmpty() const;
    void returnItem(const Item& item);
    void printSummary() const;
    bool transferItemToHero(const std::string& location, Hero& hero);
    void addItem(const Item& item);
    void loadFromDefinitions();
    std::vector<Item> drawRandomItems(int count);
    
};     