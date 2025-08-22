#include "VisitDetectiveCard.h"
#include <SFML/Graphics.hpp>
#include <iostream>


static const char* kFontPath = "../build/ManufacturingConsent-Regular.ttf";

static const char* kCardImagePath = "../build/Perk_Cards/VisitFromTheDetective.png";

void VisitDetectiveCard::apply(Hero& currentHero , std::vector<Hero*>& , std::vector<Monster*>& , ItemBag& , Map& map , bool& )
{
    std::vector<std::string> locations = map.getAllLocationNames();
    if (locations.empty())
    {
        std::cerr << "No locations available.\n";
        return;
    }

    sf::RenderWindow modal(sf::VideoMode(720 , 560) , "Visit Detective" , sf::Style::Titlebar | sf::Style::Close);
    modal.setVerticalSyncEnabled(true);

    sf::Font font;
    if (!font.loadFromFile(kFontPath))
    {
        std::cerr << "Failed to load font!\n";
    }

    sf::Texture cardTex;
    bool hasCardImage = cardTex.loadFromFile(kCardImagePath);
    sf::Sprite cardSprite;
    if (hasCardImage)
    {
        cardSprite.setTexture(cardTex);

        float scale = 0.5f;
        cardSprite.setScale(scale , scale);
        cardSprite.setPosition(24.f , 24.f);
    }

    sf::Text title;
    title.setFont(font);
    title.setCharacterSize(26);
    title.setFillColor(sf::Color::White);
    title.setString("Visit Detective");
    title.setPosition(hasCardImage ? 340.f : 24.f , 30.f);

    sf::Text desc;
    desc.setFont(font);
    desc.setCharacterSize(18);
    desc.setFillColor(sf::Color(220 , 220 , 220));
    desc.setString("Choose a destination to move your hero there.");
    desc.setPosition(hasCardImage ? 340.f : 24.f , 70.f);

    struct Button
    {
        sf::RectangleShape rect;
        sf::Text label;
        std::string value;
    };

    std::vector<Button> buttons;
    buttons.reserve(locations.size());

    const float leftX  = hasCardImage ? 340.f : 24.f;
    const float topY   = 120.f;
    const float btnW   = 320.f;
    const float btnH   = 40.f;
    const float gapX   = 20.f;
    const float gapY   = 12.f;
    const int   cols   = 2;

    for (size_t i = 0 ; i < locations.size() ; i++)
    {
        int col = static_cast<int>(i % cols);
        int row = static_cast<int>(i / cols);

        Button b;
        b.value = locations[i];

        b.rect.setSize(sf::Vector2f(btnW , btnH));
        b.rect.setFillColor(sf::Color(60 , 60 , 60));
        b.rect.setOutlineThickness(2.f);
        b.rect.setOutlineColor(sf::Color(100 , 100 , 100));
        b.rect.setPosition(leftX + col * (btnW + gapX) , topY  + row * (btnH + gapY));

        b.label.setFont(font);
        b.label.setCharacterSize(18);
        b.label.setFillColor(sf::Color::White);
        b.label.setString(locations[i]);
        b.label.setPosition(b.rect.getPosition().x + 10.f , b.rect.getPosition().y + 8.f);

        buttons.push_back(std::move(b));
    }

    while (modal.isOpen())
    {
        sf::Event e;
        while (modal.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                modal.close();
            }

            if (e.type == sf::Event::MouseMoved)
            {
                sf::Vector2f mpos = modal.mapPixelToCoords(sf::Mouse::getPosition(modal));
                for (auto& b : buttons) 
                {
                    if (b.rect.getGlobalBounds().contains(mpos))
                    {
                        b.rect.setFillColor(sf::Color(80 , 80 , 80));
                    } else {
                        b.rect.setFillColor(sf::Color(60 , 60 , 60));
                    }
                }
            }

            if (e.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mpos = modal.mapPixelToCoords(sf::Mouse::getPosition(modal));
                for (auto& b : buttons)
                {
                    if (b.rect.getGlobalBounds().contains(mpos))
                    {
                        try {
                            currentHero.move(b.value);
                            map.placeHero(&currentHero, b.value);
                        } catch (const std::exception& ex) {
                            std::cerr << "error: " << ex.what() << "\n";
                        }
                        modal.close();
                        break;
                    }
                }
            }
        }

        modal.clear(sf::Color(30 , 30 , 30));
        if (hasCardImage) modal.draw(cardSprite);
        modal.draw(title);
        modal.draw(desc);
        for (auto& b : buttons)
        {
            modal.draw(b.rect);
            modal.draw(b.label);
        }
        modal.display();
    }
}
