#pragma once
#include <string>
#include <vector>

class Map;
class Monster;
class Hero;
class Dice;

class MonsterCard
{
public:
    virtual ~MonsterCard() = default;

    virtual std::string get_name() const = 0;
    virtual std::string get_description() const = 0;

    virtual void apply(Map& map , std::vector<Monster*>& monsters , std::vector<Hero*>& heroes , Dice& dice) = 0;
};