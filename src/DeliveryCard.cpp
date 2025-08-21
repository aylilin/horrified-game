#include "../include/DeliveryCard.h"
#include "../include/map.h"
#include "../include/monster.h"
#include "../include/hero.h"
#include "../include/villager.h"
#include "../include/dice.h"
#include "../include/game-controller.h"

#include <iostream>

sf::Texture DeliveryCard::texture;
bool DeliveryCard::texture_loaded = false;


DeliveryCard::DeliveryCard()
{
    if (!texture_loaded)
    {
        if (texture.loadFromFile("../build/Monster_Cards/TheDelivery.png"))
        {
            texture_loaded = true;
            std::cout << "Delivery card texture loaded successfully!" << std::endl;
        } else {
            std::cerr << "Failed to load delivery card texture!" << std::endl;
        }
    }
    
    if (texture_loaded)
    {
        sprite.setTexture(texture);
    }
}

std::string DeliveryCard::get_name() const
{
    return "Delivery";
}

std::string DeliveryCard::get_description() const
{
    return "Invisible Man moves 2 steps, attacks once, and a villager appears.";
}

void DeliveryCard::apply(Map& map , std::vector<Monster*>& monsters , std::vector<Hero*>& heroes , Dice& dice , GameController& controller)
{
    auto items = map.get_itemBag().drawRandomItems(3);
    for (const auto& item : items)
    {
        map.placeItem(item);
    }

    Monster* invisibleMan = nullptr;

    for (Monster* m : monsters)
    {
        if (m->get_name() == "Invisible Man")
        {
            invisibleMan = m;
            break;
        }
    }

    if (!invisibleMan)
    {
        std::cout << "Invisible Man is not in the game\n";
        return;
    }

    //moving 2 steps
    map.moveMonster(invisibleMan , 2 , dice);

    std::vector<DiceFace> faces = dice.rollMultiple(3);

    int strikes = dice.countStrikes(faces);
    int powers = dice.countPowers(faces);

    if (strikes > 0)
    {
        map.monsterStrike(invisibleMan , strikes , heroes , controller);
    }

    if (powers > 0)
    {
        std::cout << "Invisible Man's power activated\n";
    }

    Villager* v = new Villager("Unnamed" , "Hospital");
    v->set_location(invisibleMan->get_currentLocation());
    map.addVillager(v);

    std::cout << "there is one villager " << invisibleMan->get_currentLocation() << "\n";
    this->show_monster_card();
}

void DeliveryCard::show_monster_card() const
{
    if (!texture_loaded)
    {
        std::cerr << "texture not loaded!" << std::endl;
        return;
    }

    sf::RenderWindow window(sf::VideoMode(800 , 600) , "Delivery Card");
    
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
