#include "BreakOfDawnCard.h"
#include "hero.h"
#include "monster.h"
#include "itemBag.h"
#include "map.h"
#include <SFML/Graphics.hpp>
#include <iostream>

BreakOfDawnCard::BreakOfDawnCard() {}

BreakOfDawnCard::BreakOfDawnCard(sf::Font& font , const sf::Texture& texture)
{
    cardSprite.setTexture(texture);
    cardSprite.setScale(0.5f , 0.5f);
    cardSprite.setPosition(400.f , 200.f);

    titleText.setFont(font);
    titleText.setString("Break of Dawn");
    titleText.setCharacterSize(24);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(420.f , 220.f);

    descriptionText.setFont(font);
    descriptionText.setString("Skip next Monster Phase and draw 2 items");
    descriptionText.setCharacterSize(18);
    descriptionText.setFillColor(sf::Color::White);
    descriptionText.setPosition(420.f , 260.f);
}

std::string BreakOfDawnCard::get_name() const 
{ 
    return "Break of Dawn"; 
}

std::string BreakOfDawnCard::get_description() const 
{ 
    return "Move the hero 2 spaces."; 
}

void BreakOfDawnCard::render(sf::RenderWindow& window)
{
    window.draw(cardSprite);
    window.draw(titleText);
    window.draw(descriptionText);
    window.draw(useButton);
    window.draw(buttonText);
}

bool BreakOfDawnCard::handleClick(sf::Vector2f mousePos , Hero& currentHero , std::vector<Hero*>& allHeroes , std::vector<Monster*>& monsters , ItemBag& bag , Map& map , bool& skipMonsterPhase)
{
    if (useButton.getGlobalBounds().contains(mousePos))
    {
        apply(currentHero , allHeroes , monsters , bag , map , skipMonsterPhase);
        return true;
    }
    return false;
}

std::string BreakOfDawnCard::getImagePath() const 
{
    return "../build/Perk_Cards/BreakOfDawn.png";
}

void BreakOfDawnCard::apply(Hero& currentHero , std::vector<Hero*>& allHeroes , std::vector<Monster*>& monsters , ItemBag& bag , Map& map , bool& skipMonsterPhase)
{
    skipMonsterPhase = true;
    std::cout << "Next Monster Phase will be skipped!\n";

    auto drawnItems = bag.drawRandomItems(2);
    if (!drawnItems.empty())
    {
        for (const auto& item : drawnItems)
        {
            map.placeItem(item);
            std::cout << "Item drawn and placed: " << item.toString() << "\n";
        }
    } else {
        std::cout << "No items were drawn.\n";
    }
}