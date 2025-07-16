#pragma once
#include <SFML/Graphics.hpp>
#include "locations.h"

enum class GameState
{
    MainMenu , InGame
};

class GameView
{
public:
    GameView();
    void run();         //main loop
    void drawMap(sf::RenderWindow& window);
    // Position getLocationPosition(const std::string& location) const;
    void showHeroSelection(sf::RenderWindow& window , sf::Font& font , std::vector<sf::RectangleShape>& buttons, std::vector<sf::Text>& labels);


private:
    sf::RenderWindow window;

    void processEvents();
    void render();
    void update();
    sf::Texture mapTexture;
    sf::Sprite mapSprite;
    std::map<std::string , Position> locations;
};