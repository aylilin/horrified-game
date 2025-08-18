#include "HurryCard.h"
#include <iostream>

HurryCard::HurryCard() {
    if (!texture.loadFromFile("assets/perk_cards/hurry.png")) {
        std::cerr << "Failed to load Hurry card image!\n";
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

void HurryCard::apply(Hero& currentHero, std::vector<Hero*>&,
                      std::vector<Monster*>&, ItemBag&, Map& map, bool&) {
    std::cout << "Select a location to move hero 2 steps.\n";

    std::string currentLoc = currentHero.get_location();
    std::cout << "Current location: " << currentLoc << "\n";

    auto neighbors = map.getConnections(currentLoc);
    std::cout << "Connected locations: ";
    for (const auto& n : neighbors) {
        std::cout << n << " ";
    }
    std::cout << "\n";

    std::string destination;
    std::cout << "Enter destination within 2 steps: ";
    std::cin >> destination;

    bool valid = false;
    if (map.areConnected(currentLoc, destination)) {
        valid = true;
    } else {
        for (const auto& first : neighbors) {
            if (map.areConnected(first, destination)) {
                valid = true;
                break;
            }
        }
    }

    if (valid) {
        currentHero.set_location(destination);
        map.placeHero(&currentHero, destination);
        std::cout << "Hero moved to " << destination << "\n";
    } else {
        std::cout << "Invalid destination for 2 steps.\n";
    }
}

void HurryCard::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(descriptionText);
    window.draw(useButton);
    window.draw(buttonText);
}

bool HurryCard::handleEvent(const sf::Event& event,
                            Hero& currentHero, std::vector<Hero*>& allHeroes,
                            std::vector<Monster*>& monsters, ItemBag& bag,
                            Map& map, bool& skipMonsterPhase) {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (useButton.getGlobalBounds().contains(mousePos)) {
            apply(currentHero, allHeroes, monsters, bag, map, skipMonsterPhase);
            return true;
        }
    }
    return false;
}

