#include <cstdlib>
#include <ctime>

#include "../include/game-controller.h"
int main()
{
    srand(time(nullptr)); 
    GameController game;
    game.run();
}