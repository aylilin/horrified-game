#include "../include/HurriedAssistantCard.h"
#include "../include/villager.h"
#include "../include/map.h"
#include "../include/dice.h"

#include <iostream>

sf::Texture HurriedAssistantCard::texture;
bool HurriedAssistantCard::texture_loaded = false;

HurriedAssistantCard::HurriedAssistantCard()
{
    if (!texture_loaded)
    {
        if (texture.loadFromFile("../build/Monster_Cards/HurriedAssistant.png"))
        {
            texture_loaded = true;
            std::cout << "HurriedAssistant card texture loaded successfully!" << std::endl;
        }
        else
        {
            std::cerr << "Failed to load HurriedAssistant card texture!" << std::endl;
        }
    }

    if (texture_loaded)
    {
        sprite.setTexture(texture);
    }
}

std::string HurriedAssistantCard::get_name() const
{
    return "Hurried Assistant";
}

std::string HurriedAssistantCard::get_description() const
{
    return "Fritz appears at Tower. Dracula moves 2 steps and strikes if present";
}

void HurriedAssistantCard::apply(Map& map , std::vector<Monster*>& monsters , std::vector<Hero*>& heroes , Dice& dice , GameController& controller)
{
    std::vector<Item> items = map.get_itemBag().drawRandomItems(3);
    for (const auto &item : items)
    {
        map.placeItem(item);
    }

    Monster* Dracula = nullptr;

    for (Monster* m : monsters)
    {
        if (m->get_name() == "Dracula")
        {
            Monster* Dracula = dynamic_cast<Monster*>(m);
            break;
        }
    }
    if (!Dracula)
    {
        std::cout << "Dracula is not in the game!\n";
        return;
    }

    // move 2 steps
    map.moveMonster(Dracula , 2 , dice);
    std::cout << "Dracula moved 2 steps.\n";

    // 4 dice and attack
    std::vector<DiceFace> faces = dice.rollMultiple(3);
    int strikes = dice.countStrikes(faces);

    map.monsterStrike(Dracula , strikes , heroes , controller);
    this->show_monster_card();

}
void HurriedAssistantCard::show_monster_card() const
{
    if (!texture_loaded)
    {
        std::cerr << "texture not loaded!" << std::endl;
        return;
    }

    sf::RenderWindow window(sf::VideoMode(800 , 600) , "HurriedAssistant Card");

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