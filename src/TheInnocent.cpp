#include "../include/TheInnocent.h"
#include "../include/villager.h"
#include "../include/map.h"
#include "../include/dice.h"
#include "../include/monster.h"
#include "../include/hero.h"

#include <iostream>

sf::Texture TheInnocentCard::texture;
bool TheInnocentCard::texture_loaded = false;

TheInnocentCard::TheInnocentCard()
{
    if (!texture_loaded)
    {
        if (texture.loadFromFile("../build/Monster_Cards/TheInnocent.png"))
        {
            texture_loaded = true;
            std::cout << "TheInnocent card texture loaded successfully!" << std::endl;
        }
        else{
            std::cerr << "Failed to load TheInnocent card texture!" << std::endl;
        }
    }

    if (texture_loaded)
    {
        sprite.setTexture(texture);
    }
}

std::string TheInnocentCard::get_name() const
{
    return "The Innocent";
}

std::string TheInnocentCard::get_description() const
{
    return "Maria appears at Barn.Dracula moves 1 step and strikes if anyone is there.";
}


void TheInnocentCard::apply(Map& map , std::vector<Monster*>& monsters , std::vector<Hero*>& heroes , Dice& dice , GameController& controller)
{
    //add items
    auto items = map.get_itemBag().drawRandomItems(3);
    for (const auto& item : items)
    {
        map.placeItem(item);
    }

    Villager* Maria = new Villager("Maria" , "Barn");
    Maria->set_location("Barn");
    map.addVillager(Maria);
    std::cout << "Maria has appeared at Barn.\n";

    //find Dracula
    Monster* Dracula = nullptr;
    for (Monster* m : monsters)
    {
        if (m->get_name() == "Dracula")
        {
            Dracula = m;
            break;
        }
    }

    if (!Dracula)
    {
        std::cout << "Dracula is not in the game.\n";
        return;
    }

    //move 1 step
    map.moveMonster(Dracula , 1 , dice);
    std::cout << "Dracula moved one step.\n";

    //2 dice for attack
    std::vector<DiceFace> faces = dice.rollMultiple(2);
    int strikes = dice.countStrikes(faces);

    map.monsterStrike(Dracula , strikes , heroes , controller);
    this->show_monster_card();

}
void TheInnocentCard::show_monster_card() const
{
    if (!texture_loaded)
    {
        std::cerr << "texture not loaded!" << std::endl;
        return;
    }

    sf::RenderWindow window(sf::VideoMode(800 , 600) , "The Innocent Card");
    
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