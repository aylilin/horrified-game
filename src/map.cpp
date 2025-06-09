#include "../include/map.h"
#include <iostream>

Map::Map() 
{
    std::vector<std::string> locations = 
    {"Cave", "Barn", "Laboratory", "Inn", "Theater", "Graveyard",
    "Crypt", "Tower", "Dungeon", "Docks", "Precinct", "Museum"};

    for (const auto& loc : locations)
    {
        addLocation(loc);
    }


    connectLocations("Cave", "Barn");
    connectLocations("Barn", "Laboratory");
    connectLocations("Laboratory", "Inn");
    connectLocations("Inn", "Theater");
    connectLocations("Graveyard", "Crypt");
    connectLocations("Crypt", "Tower");
    connectLocations("Tower", "Dungeon");
    connectLocations("Dungeon", "Docks");
    connectLocations("Docks", "Precinct");
    connectLocations("Precinct", "Museum");
    connectLocations("Museum", "Graveyard");
}

void Map::addLocation(const std::string& name) 
{
    adjacencyList[name];
}

void Map::connectLocations(const std::string& from, const std::string& to) 
{
    adjacencyList[from].insert(to);
    adjacencyList[to].insert(from);
}

bool Map::areConnected(const std::string& from, const std::string& to) const 
{
    auto it = adjacencyList.find(from);
    if (it == adjacencyList.end()) 
    {
        return false;
    }
    return it->second.count(to) > 0;
}

void Map::placeItem(const Item& item) 
{
    itemsInLocation[item.get_location()].push_back(item);
}

const std::vector<Item>& Map::get_itemsAt(const std::string& location) const {
    static std::vector<Item> empty;
    auto it = itemsInLocation.find(location);
    return (it != itemsInLocation.end()) ? it->second : empty;
}

std::vector<Item>& Map::get_itemsAt(const std::string& location) 
{
    return itemsInLocation[location];
}

void Map::set_characterLocation(const std::string& characterName, const std::string& location) 
{
    characterPositions[characterName] = location;
}

std::string Map::get_characterLocation(const std::string& characterName) const 
{
    auto it = characterPositions.find(characterName);
    if (it != characterPositions.end()) return it->second;
    return "Unknown";
}

bool Map::moveCharacter(const std::string& characterName, const std::string& toLocation) 
{
    std::string current = get_characterLocation(characterName);
    if (areConnected(current, toLocation)) 
    {
        characterPositions[characterName] = toLocation;
        return true;
    }
    return false;
}

void Map::printMap() const 
{
    std::cout << "Game Map:\n";
    for (const auto& pair : adjacencyList) {
        std::cout << "- " << pair.first << " connected to: ";
        for (const auto& neighbor : pair.second) 
        {
            std::cout << neighbor << " ";
        }
        std::cout << "\n";
    }
}

void Map::printItems() const 
{
    std::cout << "Items on Map:\n";
    for (const auto& [loc, items] : itemsInLocation) 
    {
        std::cout << loc << ": ";
        for (const auto& item : items) {
            std::cout << item.toString() << ", ";
        }
        std::cout << "\n";
    }
}

void Map::addVillager(const Villager& v)
{
    villagers.push_back(v);
}

std::vector<Villager*> Map::get_villagersAt(const std::string& location)
{
    std::vector<Villager*> result;

    for (Villager& v : villagers)
    {
        if (v.get_currentLocation() == location && v.isAlive())
        {
            result.push_back(&v);
        }
    }
    return result;
}
