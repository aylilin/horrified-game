#pragma once

#include "monsterCard.h"
#include "itemBag.h"
#include "map.h"
#include "hero.h"
#include "dice.h"

class GameController;

class FortuneTellerCard : public MonsterCard
{
public:
    std::string get_name() const override;
    std::string get_description() const override;
    void apply(Map& map, std::vector<Monster*>& monsters, std::vector<Hero*>& heroes, Dice& dice , GameController& controller);
};
