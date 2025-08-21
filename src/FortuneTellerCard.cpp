#include "../include/FortuneTellerCard.h"
#include "../include/villager.h"
#include "../include/itemBag.h"
#include "../include/game-controller.h"

#include <iostream>

sf::Texture FortuneTellerCard::texture;
bool FortuneTellerCard::texture_loaded = false;


FortuneTellerCard::FortuneTellerCard()
{
    if (!texture_loaded)
    {
        if (texture.loadFromFile("../build/Monster_Cards/FortuneTeller.png"))
        {
            texture_loaded = true;
            std::cout << "Fortune Teller card texture loaded successfully!" << std::endl;
        }
        else{
            std::cerr << "Failed to load Fortune Teller card texture!" << std::endl;
        }
    }

    if (texture_loaded)
    {
        sprite.setTexture(texture);
    }
}

std::string FortuneTellerCard::get_name() const
{
    return "Fortune Teller";
}

std::string FortuneTellerCard::get_description() const
{
    return "Add 3 items. Place Maleva at Camp. Strike: 1 move + 2 dice (Frenzied Monster)";
}

void FortuneTellerCard::apply(Map& map , std::vector<Monster*>& monsters , std::vector<Hero*>& , Dice& dice , GameController& controller)
{
    std::vector<Item> items = map.get_itemBag().drawRandomItems(3);
    for (const auto& item : items)
    {
        map.placeItem(item);
    }

    Villager* maleva = new Villager("Maleva", "Shop"); // safeLocation = Shop
    maleva->set_location("Camp");
    map.addVillager(maleva);
    std::cout << "Maleva appeared at Camp.\n";
    this->show_monster_card();

}

void FortuneTellerCard::show_monster_card() const
{
    if (!texture_loaded)
    {
        std::cerr << "texture not loaded!" << std::endl;
        return;
    }

    sf::RenderWindow window(sf::VideoMode(800 , 600) , "Fortune Teller card");
    
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
                window.close();
            
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
