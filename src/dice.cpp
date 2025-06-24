#include "../include/dice.h"

#include <cstdlib>
#include <ctime>
#include <vector>

Dice::Dice()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

DiceFace Dice::rollOne()
{
    int r = std::rand() % 6;

    if (r < 2) return DiceFace::Blank;       // 2/6 
    else if (r < 4) return DiceFace::Strike; // 2/6
    else return DiceFace::Power;             // 2/6
}

std::vector<DiceFace> Dice::rollMultiple(int count)
{
    std::vector<DiceFace> results;
    for (int i = 0 ; i < count ; ++i)
        results.push_back(rollOne());
    return results;
}
