#include "../include/GameView.h"

GameView::GameView() : window(sf::VideoMode(1024 , 768) , "Horrified")
{
    window.setFramerateLimit(60);
}

void GameView::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void GameView::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void GameView::update()
{
    // later : update positions , animations , game logic
}

void GameView::render()
{
    window.clear(sf::Color::Red);
    // TODO : draw map , items , heroes , etc.
    window.display();
}

void GameView::showHeroSelection(sf::RenderWindow& window , sf::Font& font , std::vector<sf::RectangleShape>& buttons , std::vector<sf::Text>& labels)
{
    std::vector<std::string> availableHeroes = 
    {"Archaeologist" , "Mayor" , "Courier" , "Scientist"};

    float startY = 200.f;

    for (size_t i = 0 ; i < availableHeroes.size() ; i++)
    {
        sf::RectangleShape button(sf::Vector2f(300.f , 50.f));
        button.setFillColor(sf::Color(100,100,250));
        button.setPosition(250.f , startY + i * 70.f);

        sf::Text label(availableHeroes[i] , font , 22);
        label.setFillColor(sf::Color::White);
        label.setPosition(button.getPosition().x + 20 , button.getPosition().y + 10);

        buttons.push_back(button);
        labels.push_back(label);
    }
    
}