#pragma once

#include "perkCard.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Hero;
class Monster;
class ItemBag;
class Map;

class BreakOfDawnCard : public PerkCard 
{
private:
    sf::Sprite cardSprite;
    sf::Text titleText;
    sf::Text descriptionText;
    sf::RectangleShape useButton;
    sf::Text buttonText;

public:
    std::string get_name() const override;
    std::string get_description() const override;

    BreakOfDawnCard();
    BreakOfDawnCard(sf::Font& font , const sf::Texture& texture);

    void apply(Hero& currentHero , std::vector<Hero*>& allHeros , std::vector<Monster*>& monsters , ItemBag& bag , Map& map , bool& skipMonsterPhase) override;


    bool handleClick(sf::Vector2f mousePos , Hero& currentHero , std::vector<Hero*>& allHeroes , std::vector<Monster*>& monsters , ItemBag& bag , Map& map , bool& skipMonsterPhase);

    void render(sf::RenderWindow& window);

    std::string getImagePath() const override;
    
};