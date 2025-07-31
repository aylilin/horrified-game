#pragma once
#include <SFML/Graphics.hpp>

#include "../include/game-controller.h"

enum class Screen
{
    Main , Input , HeroSelection , Map
};


class GameView
{
public:
    GameView();
    ~GameView();
    void run();        //main loop

private:
    sf::RenderWindow window;
    Screen currentScreen;
    GameController* gameController;

    sf::Texture bgTexture;
    sf::Sprite bgSprite;
    sf::RectangleShape startButton;
    sf::RectangleShape exitButton;
    sf::Text startText;
    sf::Text exitText;
    sf::Font font;

    void loadResources();
    void handleEvents();
    void render();
};