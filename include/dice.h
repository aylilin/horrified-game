#pragma once
#include <string>
#include <vector>

enum class DiceFace
{
    Strike,
    Power,  
    Blank  
};

class Dice 
{
public:
    Dice();
    
    DiceFace rollOne();
    std::vector<DiceFace> rollMultiple(int);
    int countStrikes(const std::vector<DiceFace>& faces);
    int countPowers(const std::vector<DiceFace>& faces) const;
};
