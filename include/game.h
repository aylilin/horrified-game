#pragma once

#include <SFML/Graphics.hpp>
#include "game-controller.h"

#include <vector>
#include <string>
#include <map>

class Game
{
public:
    Game(sf::RenderWindow& window);
    void startGame();

private:
    sf::Font gameFont;
    sf::RenderWindow& window;
    bool typingName;
    std::string nameInput, timeInput;
    int currentPlayerIndex;
    std::vector<std::string> playerNames, playerTimes;
    bool inputDone;

    GameController controller;
    void renderActionMenu(sf::RenderWindow& window);
    void handleActionMenuClick(const sf::Vector2f& mousePos);


    std::vector<std::string> heroList;
    std::vector<sf::RectangleShape> heroButtons;
    std::vector<sf::Text> heroLabels;
    bool gamePlayStarted;
    std::vector<std::string> selectedHeroes;
    int currentHeroPlayer;

    std::map<std::string, sf::Texture> heroTextures;
    std::map<std::string, sf::Sprite> heroSprites;
    std::map<std::string, std::string> heroStartingLocations;
    std::map<std::string, sf::RectangleShape> locationHitboxes;


    sf::Texture bgTexture, inputBgTexture, mapTexture, draculaTexture, invisibleTexture;
    sf::Texture courierTexture, scientistTexture, archaeologistTexture, mayorTexture;
    sf::Sprite bgSprite, inputBgSprite, mapSprite, draculaSprite, invisibleSprite;
    sf::Sprite courierSprite, scientistSprite, archaeologistSprite, mayorSprite;
    sf::Font font;
    sf::RectangleShape startButton, exitButton, nameBox, timeBox, continueButton;
    sf::Text startText, exitText, nameLabel, nameText, timeLabel, timeText, continueText, titleText;
};
