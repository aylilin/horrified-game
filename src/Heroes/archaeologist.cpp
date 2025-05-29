#include "archaeologist.h"
#include <stdexcept>

Archaeologist::Archaeologist(const std::string& name , const std::string& startLocation)
: Hero(name , 4 , startLocation)
{
    if (name.empty())
    {
        throw std::invalid_argument("archaeologist's name could not be empty!");
    }

    if (startLocation.empty())
    {
        throw std::invalid_argument("startlocation could not be empty!");
    }
}

void Archaeologist::specialAction()
{
    if (remainingActions <= 0)
    {
        throw std::runtime_error("there is not enough action...");
    }

    std::vector<std::string> neighborItems = 
    { "tablet" , "violin" , "scroll of thoth" };
    for (const auto& item : neighborItems)
    {
        items.push_back(item);
        std::cout << "item : " << item << "picked up from neighbor location." << 
    }
    remainingActions--;
}