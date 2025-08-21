#include "../include/EgyptianExpert.h"
#include "../include/villager.h"
#include "../include/map.h"
#include "../include/dice.h"

#include <iostream>

sf::Texture EgyptianExpertCard::texture;
bool EgyptianExpertCard::texture_loaded = false;


EgyptianExpertCard::EgyptianExpertCard()
{
    if (!texture_loaded)
    {
        if (texture.loadFromFile("../build/Monster_Cards/EgyptianExpert.png"))
        {
            texture_loaded = true;
            std::cout << "EgyptianExpert card texture loaded successfully!" << std::endl;
        }
        else{
            std::cerr << "Failed to load EgyptianExpert card texture!" << std::endl;
        }
    }

    if (texture_loaded)
    {
        sprite.setTexture(texture);
    }
}

std::string EgyptianExpertCard::get_name() const
{
    return "Egyptian Expert";
}

std::string EgyptianExpertCard::get_description() const
{
    return "place Prof. Pearson at Cave. Dracula move 1 step and strikes 2 dice.";
}

void EgyptianExpertCard::apply(Map& map , std::vector<Monster*>& monsters , std::vector<Hero*>& heroes , Dice& dice , GameController& controller)
{
    // add 3 items
    auto items = map.get_itemBag().drawRandomItems(3);
    for (const auto &item : items)
    {
        map.placeItem(item);
    }

    // add villager
    Villager *Pearson = new Villager("Prof. Pearson" , "Museum");
    Pearson->set_location("Cave");
    map.addVillager(Pearson);
    std::cout << "Prof. Pearson appeared at Cave.\n";

    for (Monster* m : monsters)
    {
        if (m->get_name() == "Dracula")
        {
            map.moveMonster(m , 1 , dice);
            auto faces = dice.rollMultiple(2);
            int strikes = dice.countStrikes(faces);
            map.monsterStrike(m , strikes , heroes , controller);
        }
    }
    this->show_monster_card();
}

void EgyptianExpertCard::show_monster_card() const
{
    if (!texture_loaded)
    {
        std::cerr << "texture not loaded!" << std::endl;
        return;
    }

    sf::RenderWindow window(sf::VideoMode(800 , 600) , "Egyptian Expert card");
    
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