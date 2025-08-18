#pragma once

#include "perkCard.h"

#include <SFML/Graphics.hpp>

class LateIntoNightCard : public PerkCard {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Font font;
    sf::Text descriptionText;
    sf::RectangleShape useButton;
    sf::Text buttonText;

public:
    LateIntoNightCard();

    std::string get_name() const override { return "Late Into Night"; }
    std::string get_description() const override { return "Gain 2 extra actions this turn."; }

    void apply(Hero& currentHero, std::vector<Hero*>& allHeroes,
               std::vector<Monster*>& monsters, ItemBag& bag, Map& map,
               bool& skipMonsterPhase) override;

    void draw(sf::RenderWindow& window);
    bool handleEvent(const sf::Event& event, Hero& currentHero);

    std::string getImagePath() const override {
    return "assets/perkcards/break_of_dawn.png";
    }
};
