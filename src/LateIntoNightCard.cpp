#include "LateIntoNightCard.h"
#include <iostream>

LateIntoNightCard::LateIntoNightCard() {

    if (!texture.loadFromFile("assets/perk_cards/late_into_night.png")) {
        std::cerr << "Failed to load Late Into Night card image!\n";
    }
    sprite.setTexture(texture);
    sprite.setScale(0.5f, 0.5f);
    sprite.setPosition(200, 100);


    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        std::cerr << "Failed to load font!\n";
    }

    descriptionText.setFont(font);
    descriptionText.setString(get_description());
    descriptionText.setCharacterSize(18);
    descriptionText.setFillColor(sf::Color::White);
    descriptionText.setPosition(200, 320);


    useButton.setSize(sf::Vector2f(120, 40));
    useButton.setFillColor(sf::Color(50, 150, 50));
    useButton.setPosition(250, 380);

    buttonText.setFont(font);
    buttonText.setString("Use");
    buttonText.setCharacterSize(20);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(280, 385);
}

void LateIntoNightCard::apply(Hero& currentHero, std::vector<Hero*>&,
                              std::vector<Monster*>&, ItemBag&, Map&,
                              bool&) {

    currentHero.addExtraActions(2);
    std::cout << "[Late Into Night] " << currentHero.get_name()
              << " gains 2 extra actions this turn.\n";
}

void LateIntoNightCard::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(descriptionText);
    window.draw(useButton);
    window.draw(buttonText);
}

bool LateIntoNightCard::handleEvent(const sf::Event& event, Hero& currentHero) {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (useButton.getGlobalBounds().contains(mousePos)) {
            return true;
        }
    }
    return false;
}
