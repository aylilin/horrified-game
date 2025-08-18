#pragma once
#include <vector>
#include <string>

class Hero;
class Monster;
class Map;
class ItemBag;

class PerkCard
{
public:
    virtual ~PerkCard() = default;

    virtual std::string get_name() const = 0;
    virtual std::string get_description() const = 0;
    virtual void apply(Hero& currentHero , std::vector<Hero*>&allHeros , std::vector<Monster*>&monsters , ItemBag& bag , Map& map , bool& skipMonsterPhase) = 0;
    virtual std::string getImagePath() const = 0;
};