#include "../include/dice.h"
#include <cstdlib>
#include <ctime>
#include <vector>

Dice::Dice() 
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

int Dice::rollNumber() 
{
    return 1 + std::rand() % 6;
}

std::string Dice::rollMonsterFace() 
{
    static std::vector<std::string> faces =
    {"Attack", "Move", "Frenzy", "Blank", "Attack", "Move"};
    int index = std::rand() % faces.size();
    return faces[index];
}
