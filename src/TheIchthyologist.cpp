#include "../include/TheIchthyologist.h"
#include "../include/villager.h"
#include "../include/map.h"

#include <iostream>

sf::Texture TheIchthyologistCard::texture;
bool TheIchthyologistCard::texture_loaded = false;

TheIchthyologistCard::TheIchthyologistCard()
{
    if (!texture_loaded)
    {
        if (texture.loadFromFile("../build/Monster_Cards/TheIchtyologist.png"))
        {
            texture_loaded = true;
            std::cout << "TheIchthyologist card texture loaded successfully!" << std::endl;
        }
        else{
            std::cerr << "Failed to load TheIchthyologist card texture!" << std::endl;
        }
    }

    if (texture_loaded)
    {
        sprite.setTexture(texture);
    }
}

std::string TheIchthyologistCard::get_name() const
{
    return "The Ichthyologist";
}

std::string TheIchthyologistCard::get_description() const
{
    return "Place Dr. Read at Institute.";
}

void TheIchthyologistCard::apply(Map& map , std::vector<Monster*>& monsters , std::vector<Hero*>& heroes , Dice& dice , GameController& controller)
{
    //add 3 items
    auto items = map.get_itemBag().drawRandomItems(3);
    for (const auto& item : items)
    {
        map.placeItem(item);
    }

    //add villager
    Villager* Read = new Villager("Dr. Read" , "Camp");
    Read->set_location("Institute");
    map.addVillager(Read);
    std::cout << "Dr. Read appeared at Institute.\n";

    for (Monster* m : monsters)
    {
        if (m->get_name() == "Invisible Man")
        {
            map.moveMonster(m , 1 , dice);
            auto faces = dice.rollMultiple(2);
            int strikes = dice.countStrikes(faces);
            map.monsterStrike(m , strikes , heroes , controller);
            break;
        }
    }
    this->show_monster_card();

}
void TheIchthyologistCard::show_monster_card() const
{
    if (!texture_loaded)
    {
        std::cerr << "texture not loaded!" << std::endl;
        return;
    }

    sf::RenderWindow window(sf::VideoMode(800 , 600) , "The Ichthyologist Card");
    
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