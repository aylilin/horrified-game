#pragma once
#include "../include/monsterCard.h"

#include <SFML/Graphics.hpp>

class GameController;

class FormOfTheBatCard : public MonsterCard 
{
private:
    static sf::Texture texture;
    static bool texture_loaded;
    
    sf::Sprite sprite;

public:
    FormOfTheBatCard();
    std::string get_name() const override;
    std::string get_description() const override;
    void show_monster_card() const;

    void apply(Map& map , std::vector<Monster*>& monsters , std::vector<Hero*>& heroes , Dice& dice , GameController& controller);
};
