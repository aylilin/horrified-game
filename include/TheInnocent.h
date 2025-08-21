#pragma once
#include "monsterCard.h"
#include "game-controller.h"

class GameController;

class TheInnocentCard : public MonsterCard
{
private:
    static sf::Texture texture;
    static bool texture_loaded;
    
    sf::Sprite sprite;

public:
    TheInnocentCard();
    std::string get_name() const override;
    std::string get_description() const override;
    void show_monster_card() const;

    void apply(Map& map , std::vector<Monster*>& monsters , std::vector<Hero*>& heroes , Dice& dice , GameController& controller);
};