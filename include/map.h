#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>
#include "item.h"
#include "villager.h"

class Map
{
public:
    Map();

    void addLocation(const std::string& name);
    void connectLocations(const std::string& from , const std::string& to);
    bool areConnected(const std::string& from , const std::string& to) const;

    //for items
    void placeItem(const Item& item);
    const std::vector<Item>& get_itemsAt(const std::string& location) const;
    std::vector<Item>& get_itemsAt(const std::string& location); 

    //for monster and hero
    void set_characterLocation(const std::string& characterName , const std::string& location);
    std::string get_characterLocation(const std::string& characterName) const;

    //move on the map
    bool moveCharacter(const std::string& characterName , const std::string& toLocation);
    void addVillager(const Villager& v);
    std::vector<Villager*> get_villagersAt(const std::string& location);

    void printMap() const;
    void printItems() const;

private:
    std::map<std::string , std::set<std::string>> adjacencyList; 
    std::map<std::string , std::vector<Item>> itemsInLocation;    
    std::map<std::string , std::string> characterPositions; 
    std::vector<Villager> villagers;
};
