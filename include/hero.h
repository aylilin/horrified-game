#pragma once   //for not including headers several times
#include "item.h"
#include "itemBag.h"
#include "map.h"
#include "perkCard.h"

#include <vector>
#include <string>
#include <memory>

class Map;
class ItemBag;
class PerkCard;
class Monster;

class Hero
{
protected:
    std::string name;
    int actions;
    int remainingActions;
    std::vector<std::string> items;      //items that hero carries
    std::unique_ptr<PerkCard> perk;      //perk cart haee ke dare
    std::string currentLocation;         //where is hero?
    int extraActions = 0;
    std::vector<Item> inventory; 
    int health = 4;

public:  
    Hero(const std::string& name , int actions , const std::string& startLocation);
    virtual void specialAbility() = 0;
    virtual void addExtraActions(int count);
    virtual void resetActions();
    void addItem(const Item& item);
    void move(const std::string& newLocation);
    void pickup(ItemBag& bag);
    void dropAllItems(ItemBag& bag);
    void guide(Map& map);
    //special action is just for archeologist
    
    void set_location(const std::string& newLocation);
    std::string get_location() const;
    std::string get_name() const;
    int get_remainingActions() const;
    const std::vector<Item>& get_inventory() const;
    
    void givePerk(std::unique_ptr<PerkCard> newPerk);
    bool hasPerk() const;
    void usePerk(Map& map, std::vector<Hero*>& heroes, std::vector<Monster*>& monsters, ItemBag& bag, bool& skipMonsterPhase);


    void receiveDamage(int amount);
    int get_health() const;
    bool isAlive() const;

};