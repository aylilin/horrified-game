#pragma once
#include <string>
#include "hero.h"

class Hero;

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

    virtual void set_location(const std::string& newLoc);
    virtual void move(const std::string& newLocation);
    virtual void attack(Hero& target);
    virtual void useSpecialPower() = 0;
    virtual bool checkDefeatConditions() const = 0;
};