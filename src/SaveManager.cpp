#include "SaveManager.h"
#include <fstream>
#include <iostream>

void SaveManager::saveGame(const std::vector<Hero*>& heroes , const std::vector<Monster*>& monsters , const Map& map , int terrorLevel , const std::string& currentTurn , const std::string& currentPhase , const std::string& filename)
{
    std::ofstream out(filename);
    if (!out.is_open())
    {
        std::cerr << "Failed to open file for saving!\n";
        return;
    }

    out << "HEROES\n";
    for (const Hero* hero : heroes)
    {
        out << "Hero: " << hero->get_name() << "\n";
        out << "Location: " << hero->get_location() << "\n";
        out << "Health: " << hero->get_health() << "\n";
        out << "Perk: " << (hero->hasPerk() ? "true" : "false") << "\n";

        const auto& inv = hero->get_inventory();
        out << "Inventory:";
        for (size_t i = 0; i < inv.size(); ++i)
        {
            out << " " << inv[i].toString();
            if (i < inv.size() - 1) out << " |";
        }
        out << "\n---\n";
    }

    out << "\nMONSTERS\n";
    for (const Monster* m : monsters)
    {
        out << "Monster: " << m->get_name() << "\n";
        out << "Location: " << m->get_currentLocation() << "\n";
        out << "Dead: " << (m->get_isDead() ? "true" : "false") << "\n";
        out << "---\n";
    }

    out << "\nITEMS ON MAP\n";
    for (const auto& [loc, items] : map.get_AllItems())
    {
        for (const auto& item : items)
        {
            out << "Item: " << item.toString() << " | Location: " << loc << "\n";
        }
    }

    out << "\nGAME STATE\n";
    out << "TerrorLevel: " << terrorLevel << "\n";
    out << "CurrentTurn: " << currentTurn << "\n";
    out << "CurrentPhase: " << currentPhase << "\n";

    out.close();
    std::cout << "Game saved to " << filename << "\n";
}
