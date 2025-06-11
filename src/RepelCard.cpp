#include "RepelCard.h"
#include "../include/monster.h"
#include "../include/map.h"
#include <iostream>

std::string RepelCard::get_name() const 
{
    return "Repel";
}

std::string RepelCard::get_description() const 
{
    return "move one monster back two spaces.";
}

void RepelCard::apply(Hero& , std::vector<Hero*>& , std::vector<Monster>& monsters , ItemBag& , Map& map , bool&) 
{
    if (monsters.empty()) 
    {
        std::cout << "There is no monsters in the game...\n";
        return;
    }

    std::cout << '\t' << "***Monster Selection***\n";
    for (size_t i = 0; i < monsters.size(); ++i) 
    {
        std::cout << i + 1 << ". " << monsters[i].get_name()
        << " in " << monsters[i].get_currentLocation() << "\n";
    }

    int choice;
    std::cout << "enter monster's number : ";
    std::cin >> choice;
    std::cin.ignore();

    if (choice < 1 || choice > (int)monsters.size()) 
    {
        std::cout << "invalid choice...\n";
        return;
    }

    Monster& selected = monsters[choice - 1];
    std::string currentLocation = selected.get_currentLocation();

    std::cout << "The place you want to be moved to : " << selected.get_name() << "\n";
    std::string target;
    std::getline(std::cin, target);

    if (map.areConnected(currentLocation, target)) 
    {
        map.set_characterLocation(selected.get_name(), target);
        selected.set_location(target);
        std::cout << selected.get_name() << "moved to " << target << "\n";
    } else {
        std::cout << "This location is not connected to the current location!!!\n";
    }
}
