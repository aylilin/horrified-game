#pragma once

#include <string>
#include <vector>

#include "map.h"

class Monster;
class Hero;
class Dice;
class GameController;

class MonsterCard
{
public:
    virtual ~MonsterCard() = default;

    virtual std::string get_name() const = 0;
    virtual std::string get_description() const = 0;

    virtual void apply(Map& map , std::vector<Monster*>& monsters , std::vector<Hero*>& heroes , Dice& dice , GameController& controller) = 0;
};