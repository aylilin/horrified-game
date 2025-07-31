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

int Dice::countStrikes(const std::vector<DiceFace>& faces)
{
    int count = 0;
    for (const auto& face : faces)
    {
        if (face == DiceFace::Strike)
        {
            ++count;
        }
    }
    return count;
}

int Dice::countPowers(const std::vector<DiceFace>& faces) const
{
    int count = 0;
    for (DiceFace face : faces)
    {
        if (face == DiceFace::Power)
        count++;
    }
    return count;
}