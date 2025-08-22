#include "../include/ThiefCard.h"
#include "../include/map.h"
#include "../include/monster.h"
#include "../include/hero.h"
#include "../include/dice.h"
#include "../include/game-controller.h"

#include <iostream>
#include <unordered_map>

sf::Texture ThiefCard::texture;
bool ThiefCard::texture_loaded = false;

ThiefCard::ThiefCard()
{
    if (!texture_loaded)
    {
        if (texture.loadFromFile("../build/Monster_Cards/Thief.png"))
        {
            texture_loaded = true;
            std::cout << "Thief card texture loaded successfully!" << std::endl;
        }
        else{
            std::cerr << "Failed to load Thief card texture!" << std::endl;
        }
    }

    if (texture_loaded)
    {
        sprite.setTexture(texture);
    }
}

std::string ThiefCard::get_name() const
{
    return "Thief";
}

std::string ThiefCard::get_description() const
{
    return "Invisible Man moves 1, attacks once.";
}

void ThiefCard::apply(Map& map , std::vector<Monster*>& monsters , std::vector<Hero*>& heroes , Dice& dice , GameController& controller)
{
    auto items = map.get_itemBag().drawRandomItems(2);
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
        std::cout << "Invisible Man is not in the game...\n";
        return;
    }

    //moving one step
    std::string current = invisibleMan->get_currentLocation();
    std::string nearest = map.findNearestHeroLocation(current , heroes);

    if (!nearest.empty() && map.areConnected(current , nearest))
    {
        map.set_characterLocation(invisibleMan->get_name() , nearest);
        invisibleMan->set_location(nearest);
        std::cout << "Invisible Man moved to " << nearest << "\n";
    }else{
        std::cout << "No valid move for Invisible Man.\n";
        return;
    }

    std::vector<DiceFace> faces = dice.rollMultiple(3);
    int strikes = dice.countStrikes(faces);
    int power = dice.countPowers(faces);

    if (strikes > 0)
    {
        bool attacked = false;
        //attacks with hero
        for (Hero* h : heroes)
        {
        if (h->get_location() == invisibleMan->get_currentLocation())
        {
            invisibleMan->attack(*h);
            break;
        }
    }
    if (!attacked)
    {
        std::vector<Villager*> villagersHere = map.getVillagersAt(invisibleMan->get_currentLocation());
        if (!villagersHere.empty())
        {
            map.removeVillager(villagersHere.front());
            controller.increaseTerrorLevel();
            std::cout << "A villager was attacked by Invisible Man! Terror Level is increased.\n";
        }else{
            std::cout << "No one attacks at " << invisibleMan->get_currentLocation() << "\n";
        }
    }
    }
    if (power > 0)
    {
        std::cout << "Invisible Man used power effect...\n";
    }
    this->show_monster_card();
}

void ThiefCard::show_monster_card() const
{
    if (!texture_loaded)
    {
        std::cerr << "texture not loaded!" << std::endl;
        return;
    }

    sf::RenderWindow window(sf::VideoMode(800 , 600), "Thief card");
    
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