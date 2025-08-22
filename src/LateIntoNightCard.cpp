#include "LateIntoNightCard.h"
#include <iostream>

LateIntoNightCard::LateIntoNightCard()
{

    if (!texture.loadFromFile("../build/Perk_Cards/LateIntoTheNight.png"))
    {
        std::cerr << "Failed to load Late Into The Night card image!\n";
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
}

void LateIntoNightCard::apply(Hero& currentHero , std::vector<Hero*>& , std::vector<Monster*>& , ItemBag& , Map& , bool&)
{
    currentHero.addExtraActions(2);
    std::cout << currentHero.get_name() << " gains 2 extra actions this turn.\n";
}

void LateIntoNightCard::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    window.draw(descriptionText);
    window.draw(useButton);
    window.draw(buttonText);
}

bool LateIntoNightCard::handleEvent(const sf::Event& event , Hero& currentHero)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2f mousePos(event.mouseButton.x , event.mouseButton.y);
        if (useButton.getGlobalBounds().contains(mousePos))
        {
            return true;
        }
    }
    return false;
}
