#pragma once
#include <string>

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
};
