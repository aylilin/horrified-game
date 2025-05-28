#pragma once   //for not including headers several times
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

public:  
    Hero(const std::string& name , int actions , std::string& startLocation);
    virtual void specialAbility() = 0;
    void move(const std::string& newLocation);
    void pickup(const std::string& item);
    void guide();
    void advance();
    //void defeat(const std::string& )
    //special action is just for archeologist
    
    std::string get_name() const;
    int get_remainingActions() const;
};
