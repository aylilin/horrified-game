#include "../include/SunriseCard.h"
#include "../include/map.h"
#include "../include/monster.h"
#include "../include/hero.h"
#include "../include/villager.h"
#include "../include/dice.h"
#include "../include/game-controller.h"
#include <iostream>

sf::Texture SunriseCard::texture;
bool SunriseCard::texture_loaded = false;

SunriseCard::SunriseCard()
{
    if (!texture_loaded)
    {
        if (texture.loadFromFile("../build/Monster_Cards/Sunrise.png"))
        {
            texture_loaded = true;
            std::cout << "Sunrise card texture loaded successfully!" << std::endl;
        }
        else{
            std::cerr << "Failed to load Sunrise card texture!" << std::endl;
        }
    }

    if (texture_loaded)
    {
        sprite.setTexture(texture);
    }
}

std::string SunriseCard::get_name() const
{
    return "Sunrise";
}

std::string SunriseCard::get_description() const
{
    return "Dracula moves to Crypt , Invisible Man strikes with 3 dice.";
}

void SunriseCard::apply(Map& map , std::vector<Monster*>& monsters , std::vector<Hero*>& heroes , Dice& dice , GameController& controller)
{
    Monster* InvisibleMan = nullptr;
    Monster* Dracula = nullptr;

    for (Monster* m : monsters)
    {
        if (m->get_name() == "Dracula")
        {
            Dracula = dynamic_cast<Monster*>(m);
        }
            else if (m->get_name() == "Invisible Man")
            {
                InvisibleMan = m;
            }

            if (Dracula)
            {
                Dracula->set_location("Crypt");
                map.placeMonster(Dracula , "Crypt");
                std::cout << "Dracula moved to Crypt.\n";
            }
            
            if (InvisibleMan)
            {
                std::vector<DiceFace> faces = dice.rollMultiple(3);
                std::cout << "Invisible Man rolled 3 dice.\n";

                if (dice.countPowers(faces) > 0)
                {
                    std::cout << "Power triggered for Invisible Man!\n";
                }

                //strike and attack
                int strikes = dice.countStrikes(faces);
                if (strikes > 0)
                {
                    map.monsterStrike(InvisibleMan , strikes , heroes , controller);
                }else{
                    std::cout << "Invisible Man did not strike.\n";
                }
            }

        }
        this->show_monster_card();
    }

void SunriseCard::show_monster_card() const
{
    if (!texture_loaded)
    {
        std::cerr << "texture not loaded!" << std::endl;
        return;
    }

    sf::RenderWindow window(sf::VideoMode(800 , 600), "SunriseCard ");
    
    sf::Font font;
    if (!font.loadFromFile("ManufacturingConsent-Regular.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
    }

    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    
    sf::Sprite displaySprite = sprite;
    displaySprite.setScale(0.2f , 0.2f);
    displaySprite.setPosition(350 , 200);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            
            if (event.type == sf::Event::MouseButtonPressed)
            {
                window.close();
            }
        }

        window.clear(sf::Color(30 , 30 , 60));

        window.draw(displaySprite);

        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setString("Card Name: " + get_name());
        text.setPosition(40 , 40);
        window.draw(text);

        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Yellow);
        text.setString("Description: " + get_description());
        text.setPosition(40 , 80);
        window.draw(text);

        window.display();
    }
}
