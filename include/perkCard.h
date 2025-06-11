#pragma once
#include <vector>
#include <string>
#include "map.h"

class Hero;
class Monster;
class ItemBag;
class Map;

class PerkCard
{
public:
    virtual ~PerkCard() = default;

    virtual std::string get_name() const = 0;
    virtual std::string get_description() const = 0;
    virtual void apply(Hero& currentHero , std::vector<Hero*>&allHeros , std::vector<Monster>&monsters , ItemBag& bag , Map& map , bool& skipMonsterPhase) = 0;
};