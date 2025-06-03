#include "Dracula.h"
#include <iostream>
//#include <algorithm>
Dracula::Dracula() : Monster("Dracula") , coffinDestroyed(0) 
{
    coffins = 
    { {"cave" , false} , {"Dungeon" , false} , {"crypt" , false} , {"graveyard" , false} };
}

void Dracula::destroyCoffin(const std::string& Location)
{
    if (coffins.find(Location) != coffins.end() && !coffins[Location])
    {
        coffins[Location] = true;
        coffinDestroyed++;
        std::cout << "coffin in " << Location << " destroyed! (" << coffinDestroyed << "/4)" << std::endl;
    }
}

bool Dracula::checkDefeatConditions() const
{
    return coffinDestroyed >= 4;
}



// void Dracula::destroyCoffin(std::string Location)
// {

// }