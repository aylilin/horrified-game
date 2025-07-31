#include "GameView.h"

#include <iostream>

GameView::GameView() :
window(sf::VideoMode(800,800) , "Horrified") , currentScreen(Screen::Main)
{

    loadResources();
}

GameView::~GameView()
{
    delete gameController;
}

void GameView::loadResources()
{
    //display font
    if (!font.loadFromFile("../build/ManufacturingConsent-Regular.ttf"))
    {
        std::cerr << "Failed to load font.\n";
        exit(-1);
    }

    //display background1
    if (!bgTexture.loadFromFile("../build/Horrified.jpg"))
    {
        std::cerr << "Failed to load horrified image!\n";
        exit(-1);
    }

    bgSprite.setTexture(bgTexture);

    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = bgTexture.getSize();

    // float scale = static_cast<float>(windowSize.x) / textureSize.x , static_cast<float>(windowSize.y) / textureSize.y;
    // bgSprite.setScale(scale , scale);

    sf::FloatRect spriteBounds = bgSprite.getGlobalBounds();
    bgSprite.setPosition((windowSize.x - spriteBounds.width) / 2.f , (windowSize.y - spriteBounds.width) / 2.f);

    //start button
    startButton.setSize(sf::Vector2f(200.f , 60.f));
    startButton.setFillColor(sf::Color::Green);
    startButton.setPosition(300.f , 500.f);
    startText.setFont(font);
    startText.setString("Start");
    startText.setCharacterSize(28);
    startText.setFillColor(sf::Color::White);
    startText.setPosition(startButton.getPosition().x + 40 , startButton.getPosition().y + 10);

    //exit button
    exitButton.setSize(sf::Vector2f(200.f , 60.f));
    exitButton.setFillColor(sf::Color::Red);
    exitButton.setPosition(300.f , 580.f);
    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(28);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(exitButton.getPosition().x + 50 , exitButton.getPosition().y + 10);
}

void GameView::handleEvents()
{
    sf::Event event;
    //main loop
    while (window.pollEvent(event))
    {
        //closing window
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (currentScreen == Screen::Main && event.type == sf::Event::MouseButtonPressed)
        {
            if (startButton.getGlobalBounds().contains(mousePos))
            {
                currentScreen = Screen::Input;
            }

            if (exitButton.getGlobalBounds().contains(mousePos))
            {
                window.close();
            }
    }
}
}

void GameView::render()
{
    window.clear();
    if (currentScreen == Screen::Main)
    {
        window.draw(bgSprite);
        window.draw(startButton);
        window.draw(startText);
        window.draw(exitButton);
        window.draw(exitText);
    }
    window.display();
}

void GameView::run()
{
    while (window.isOpen())
    {
        handleEvents();
        render();
    }
}