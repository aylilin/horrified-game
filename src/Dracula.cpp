#include "Dracula.h"
#include <iostream>
//#include <algorithm>
Dracula::Dracula() : Monster("Dracula") , coffinDestroyed(0) 
{
    coffins = 
    { {"cave" , false} , {"Dungeon" , false} , {"crypt" , false} , {"graveyard" , false} };
}


// void Dracula::destroyCoffin(std::string Location)
// {

// }