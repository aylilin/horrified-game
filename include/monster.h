#pragma once
#include <string>

class Monster
{
protected:
    std::string name;
    std::string currentLocation;
    int health;
    bool isDead;

public:
    Monster(const std::string& name);
    virtual ~Monster() = default;

    std::string get_name() const;
    std::string get_currentLocation() const;
    bool get_isDead() const;

    virtual void move(const std::string& newLocation);
    virtual void attack();
    virtual void useSpecialPower() = 0;
    
};