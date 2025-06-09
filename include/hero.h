#pragma once   //for not including headers several times
#include "item.h"
#include <vector>
#include <string>

class Hero
{
protected:
    std::string name;
    int actions;
    int remainingActions;
    std::vector<std::string> items;      //items that hero carries
    std::string currentLocation;         //where hero is?
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
    void pickup(const std::string& item);
    void guide();
    void advance();
    //special action is just for archeologist
    
    void set_location(const std::string& newLocation);
    std::string get_location() const;
    std::string get_name() const;
    int get_remainingActions() const;

    void receiveDamage(int amount);
    int get_health() const;
    bool isAlive() const;

};