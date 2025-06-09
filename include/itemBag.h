#pragma once
#include <vector>
#include <string>
#include "item.h"

class ItemBag
{
private:
    std::vector<Item> items;

public:
    ItemBag();
    
    void generateRandomItems(int count);
    Item drawRandomItem();
    bool isEmpty() const;
    void returnItem(const Item& item);
    void printSummary() const;
};     