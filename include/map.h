#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <set>

#include "item.h"
#include "villager.h"
#include "hero.h"
#include "monster.h"
#include "dice.h"
#include "itemBag.h"

class Monster;
class Hero;
class Villager;
class GameController;

class Map
{
public:
    Map();
    ~Map();
 
    void addLocation(const std::string& name);
    bool areConnected(const std::string& from , const std::string& to) const;
    std::set<std::string> getConnections(const std::string& location) const;
    void connectLocations(const std::string& from , const std::string& to);

    //for items
    void placeItem(const Item& item);
    const std::vector<Item>& get_itemsAt(const std::string& location) const;
    std::vector<Item>& get_itemsAt(const std::string& location); 
    ItemBag& get_itemBag();
    const std::vector<Item>& get_getAllItems() const;


    //for monster and hero
    void set_characterLocation(const std::string& characterName , const std::string& location);
    std::string get_characterLocation(const std::string& characterName) const;

    //move on the map
    bool moveCharacter(const std::string& characterName , const std::string& toLocation);
    std::vector<Villager*> get_villagersAt(const std::string& location);
    std::vector<Hero*> getHeroesAt(const std::string& location);

    void placeHero(Hero* hero, const std::string& location);
    std::string findNearestHeroLocation(const std::string& from , const std::vector<Hero*> heroes) const;
    void placeMonster(Monster* monster, const std::string& location);
    void moveMonster(Monster* monster, int steps , Dice& dice);
    void monsterStrike(Monster* monster , int strikeCount , const std::vector<Hero*>& heroes , GameController& controller);
    void manualMoveMonster(Monster* monster);


    std::vector<Villager*> getVillagersAt(const std::string& location);
    void markVillagerAsGuided(const std::string& name);
    void displayAvailableVillagers() const;
    void addVillager(Villager* v);
    void setVillagerLocation(Villager* villager , const std::string& location);
    void removeVillager(Villager* villager);


    void printMap() const;
    void printItems() const;

private:
    std::map<std::string , std::set<std::string>> adjacencyList; 
    std::map<std::string , std::set<std::string>> connections;
    std::map<std::string , std::vector<Item>> itemsInLocation;    
    std::map<std::string , std::string> characterPositions; 
    std::map<std::string, std::vector<Hero*>> heroPositions;
    std::unordered_map<std::string , std::set<std::string>> locationConnections;
    std::vector<Villager*> villagers;
    std::map<std::string , std::vector<Villager*>> villagerPositions;
    std::vector<Item> itemsOnMap;
    std::vector<Item> items;
    ItemBag itemBag;

};
