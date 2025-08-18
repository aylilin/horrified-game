#pragma once

#include "perkCard.h"
#include "hero.h"
#include "monster.h"
#include "itemBag.h"
#include "map.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class OverstockCard : public PerkCard
{
public:
    OverstockCard();

    std::string get_name() const override { return "Overstock"; }
    std::string get_description() const override {
        return "Each hero takes 1 item from the bag and places it in their current location.";
    }

    void apply(Hero& currentHero,
               std::vector<Hero*>& allHeroes,
               std::vector<Monster*>& monsters , ItemBag& bag, Map& map, bool& skipMonsterPhase) override;

    void render(sf::RenderWindow& window);
    void handleClick(sf::Vector2f mousePos, Hero& currentHero,
                     std::vector<Hero*>& allHeroes,
                     std::vector<Monster*>& monsters,
                     ItemBag& bag, Map& map, bool& skipMonsterPhase);

    std::string getImagePath() const override {
    return "assets/perkcards/break_of_dawn.png";
    }

private:
    sf::Texture cardTexture;
    sf::Sprite cardSprite;

    sf::RectangleShape useButton;
    sf::Font font;
    sf::Text buttonText;
};
