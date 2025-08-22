#include "game.h"
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800 , 800) , "Horrified");
    
    Game game(window);

    game.startGame();
    
    return 0;
}