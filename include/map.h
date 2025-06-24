#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>
#include "item.h"
#include "villager.h"
#include "hero.h"
#include "monster.h"

class Monster;
class Hero;

class Map
{
public:
    Map();
    ~Map();
 
    void addLocation(const std::string& name);
    void connectLocations(const std::string& from , const std::string& to);
    bool areConnected(const std::string& from , const std::string& to) const;

    //for items
    void placeItem(const Item& item);
    const std::vector<Item>& get_itemsAt(const std::string& location) const;
    std::vector<Item>& get_itemsAt(const std::string& location); 
    ItemBag& get_itemBag();


    //for monster and hero
    void set_characterLocation(const std::string& characterName , const std::string& location);
    std::string get_characterLocation(const std::string& characterName) const;

    //move on the map
    bool moveCharacter(const std::string& characterName , const std::string& toLocation);
    std::vector<Villager*> get_villagersAt(const std::string& location);
    std::vector<Hero*> Map::getHeroesAt(const std::string& location);

    void placeHero(Hero* hero, const std::string& location);
    void placeMonster(Monster* monster, const std::string& location);
    void moveMonster(Monster* monster, const std::string& newLocation);


    std::vector<Villager*> getVillagersAt(const std::string& location);
    void markVillagerAsGuided(const std::string& name);
    void displayAvailableVillagers() const;
    void addVillager(Villager* v);


    void printMap() const;
    void printItems() const;

private:
    std::map<std::string , std::set<std::string>> adjacencyList; 
    std::map<std::string , std::vector<Item>> itemsInLocation;    
    std::map<std::string , std::string> characterPositions; 
    std::map<std::string, std::vector<Hero*>> heroPositions;
    std::vector<Villager*> villagers;
    std::vector<Item> itemsOnMap;
    ItemBag itemBag;

};
