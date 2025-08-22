#include "RepelCard.h"
#include <iostream>
#include "dice.h"

RepelCard::RepelCard()
{
    if (!texture.loadFromFile("../build/Perk_Cards/Repel.png"))
    {
        std::cerr << "Failed to load Repel card image!\n";
    }
    sprite.setTexture(texture);
    sprite.setScale(0.5f , 0.5f);
    sprite.setPosition(200 , 100);

    if (!font.loadFromFile("../build/ManufacturingConsent-Regular.ttf"))
    {
        std::cerr << "Failed to load font!\n";
    }

    descriptionText.setFont(font);
    descriptionText.setString(get_description());
    descriptionText.setCharacterSize(18);
    descriptionText.setFillColor(sf::Color::White);
    descriptionText.setPosition(200 , 320);

    useButton.setSize(sf::Vector2f(120 , 40));
    useButton.setFillColor(sf::Color(50 , 150 , 50));
    useButton.setPosition(250 , 380);

    buttonText.setFont(font);
    buttonText.setString("Use");
    buttonText.setCharacterSize(20);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(280 , 385);
}

void RepelCard::apply(Hero& , std::vector<Hero*>& , std::vector<Monster*>& monsters , ItemBag& , Map& map , bool&) {
    Dice dice;
    std::cout << "Move all monsters 2 steps.\n";

    for (Monster* monster : monsters)
    {
        if (monster)
        {
            map.moveMonster(monster , 2 , dice);
            std::cout << monster->get_name() << " moved 2 steps.\n";
        }
    }
}

void RepelCard::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    window.draw(descriptionText);
    window.draw(useButton);
    window.draw(buttonText);
}

bool RepelCard::handleEvent(const sf::Event& event , Hero& currentHero , std::vector<Hero*>& allHeroes , std::vector<Monster*>& monsters , ItemBag& bag , Map& map , bool& skipMonsterPhase)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2f mousePos(event.mouseButton.x , event.mouseButton.y);
        if (useButton.getGlobalBounds().contains(mousePos))
        {
            apply(currentHero , allHeroes , monsters , bag , map , skipMonsterPhase);
            return true;
        }
    }
    return false;
}
