#pragma once

#include "perkCard.h"

#include <SFML/Graphics.hpp>

class HurryCard : public PerkCard
{
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Font font;
    sf::Text descriptionText;
    sf::RectangleShape useButton;
    sf::Text buttonText;

public:
    HurryCard();

    std::string get_name() const override 
    { 
        return "Hurry"; 
    }

    std::string get_description() const override 
    { 
        return "Move hero 2 steps.";
    }

    void apply(Hero& currentHero , std::vector<Hero*>& allHeroes , std::vector<Monster*>& monsters , ItemBag& bag , Map& map , bool& skipMonsterPhase) override;
    void draw(sf::RenderWindow& window);
    bool handleEvent(const sf::Event& event , Hero& currentHero , std::vector<Hero*>& allHeroes , std::vector<Monster*>& monsters , ItemBag& bag , Map& map , bool& skipMonsterPhase);

    std::string getImagePath() const override
    {
        return "../build/Perk_Cards/BreakOfDawn.png";
    }
};
