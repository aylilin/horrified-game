#include "OverstockCard.h"
#include <iostream>

OverstockCard::OverstockCard() {
    if (!cardTexture.loadFromFile("assets/cards/overstock.png")) {
        std::cerr << "Failed to load OverstockCard texture\n";
    }
    cardSprite.setTexture(cardTexture);
    cardSprite.setPosition(300, 100);

    useButton.setSize(sf::Vector2f(150, 50));
    useButton.setFillColor(sf::Color::Green);
    useButton.setPosition(350, 400);

    font.loadFromFile("assets/fonts/arial.ttf");
    buttonText.setFont(font);
    buttonText.setString("Use Card");
    buttonText.setCharacterSize(20);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(370, 410);
}

void OverstockCard::apply(Hero& currentHero,
                          std::vector<Hero*>& allHeroes,
                          std::vector<Monster*>& monsters,
                          ItemBag& bag, Map& map, bool& skipMonsterPhase) {

    currentHero.addExtraActions(2);
    currentHero.resetActions();
    std::cout << "Added 2 extra actions to hero: "
              << currentHero.get_name() << "\n";

    for (Hero* hero : allHeroes) {
        if (!hero) continue;

        auto items = bag.drawRandomItems(1);
        if (!items.empty()) {
            Item& drawnItem = items[0];
            drawnItem.moveTo(hero->get_location());
            map.addItemToLocation(drawnItem);
            std::cout << "[Overstock] Item placed at "
                      << hero->get_location() << "\n";
        } else {
            std::cout << "No items left in the bag!\n";
        }
    }
}

void OverstockCard::render(sf::RenderWindow& window) {
    window.draw(cardSprite);
    window.draw(useButton);
    window.draw(buttonText);
}

void OverstockCard::handleClick(sf::Vector2f mousePos, Hero& currentHero,
                                std::vector<Hero*>& allHeroes,
                                std::vector<Monster*>& monsters,
                                ItemBag& bag, Map& map, bool& skipMonsterPhase) {
    if (useButton.getGlobalBounds().contains(mousePos)) {
        apply(currentHero, allHeroes, monsters, bag, map, skipMonsterPhase);
    }
}

