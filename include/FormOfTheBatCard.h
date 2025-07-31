#pragma once
#include "../include/monsterCard.h"

class GameController;

class FormOfTheBatCard : public MonsterCard 
{
public:
    std::string get_name() const override;
    std::string get_description() const override;

    void apply(Map& map , std::vector<Monster*>& monsters , std::vector<Hero*>& heroes , Dice& dice , GameController& controller);
};
