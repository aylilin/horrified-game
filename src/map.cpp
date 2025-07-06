#include "../include/map.h"
#include "../include/monster.h"
#include "../include/hero.h"
#include "../include/game-controller.h"

#include <iostream>
#include <algorithm>
#include <string>
#include <queue>


Map::Map() 
{
    std::vector<std::string> locations = 
    {"Cave", "Barn", "Laboratory", "Inn", "Theater", "Graveyard",
    "Crypt", "Tower", "Dungeon", "Docks", "Precinct", "Museum", "Camp", "Shop", "Institute" , "Mansion" , "Hospital"};

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
    connectLocations("Camp" , "Shop");
    connectLocations("Shop" , "Institute");
    connectLocations("Institute" , "Laboratory");
    connectLocations("Laboratory" , "Mansion");
    connectLocations("Mansion" , "Hospital");
    // connectLocations("Hospital" , "Barn");
}

void Map::addLocation(const std::string& name) 
{
    adjacencyList[name];
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

std::set<std::string> Map::getConnections(const std::string& location) const
{
    auto it = connections.find(location);
    if (it != connections.end())
    {
        return it->second;
    }
    return {}; // return empty set if location not found
}

void Map::connectLocations(const std::string& from , const std::string& to)
{
    locationConnections[from].insert(to);
    locationConnections[to].insert(from);
}

const std::vector<Item>& Map::get_itemsAt(const std::string& location) const
{
    static std::vector<Item> empty;
    auto it = itemsInLocation.find(location);
    return (it != itemsInLocation.end()) ? it->second : empty;
}

std::vector<Item>& Map::get_itemsAt(const std::string& location) 
{
    return itemsInLocation[location];
}

void Map::placeItem(const Item& item)
{
    itemsOnMap.push_back(item);
}

const std::vector<Item>& Map::get_getAllItems() const
{
    return items;
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

ItemBag& Map::get_itemBag()
{
    return itemBag;
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

std::vector<Villager*> Map::getVillagersAt(const std::string& location)
{
    std::vector<Villager*> result;
    for (Villager* v : villagers)
    {
        if (v->get_currentLocation() == location && !v->isGuided())
        {
            result.push_back(v);
        }
    }
    return result;
}

void Map::markVillagerAsGuided(const std::string& name)
{
    for (Villager* v : villagers)
    {
        if (v->get_name() == name)
        {
            v->set_guided(true);
            return;
        }
    }
}

void Map::printMap() const 
{
    std::cout << R"(
                           ┌────────────┐
                           │ Graveyard  │
                           └─────┬──────┘
                                 │
                           ┌─────▼──────┐
                           │   Crypt    │
                           └─────┬──────┘
                                 │
                           ┌─────▼──────┐
                           │   Tower    │
                           └─────┬──────┘
                                 │
                           ┌─────▼──────┐
                           │  Dungeon   │
                           └─────┬──────┘
                                 │
                           ┌─────▼──────┐
                           │   Docks    │
                           └─────┬──────┘
                                 │
        ┌────────────┐     ┌─────▼──────┐     ┌────────────┐
        │  Precinct  │◀───▶│  Museum    │◀───▶│  Institute  │
        └────────────┘     └─────┬──────┘     └────────────┘
                                 │
                           ┌─────▼──────┐
                           │  Theater   │
                           └─────┬──────┘
                                 │
                           ┌─────▼──────┐
                           │    Inn     │
                           └─────┬──────┘
                                 │
        ┌────────────┐     ┌─────▼──────┐     ┌────────────┐
        │ Laboratory │◀───▶│  Mansion   │◀───▶│  Hospital   │
        └────────────┘     └────────────┘     └────────────┘

        ┌────────────┐     ┌────────────┐
        │   Shop     │     │   Camp     │
        └────────────┘     └────────────┘

                           ┌────────────┐
                           │    Barn    │
                           └─────┬──────┘
                                 │
                           ┌─────▼──────┐
                           │    Cave    │
                           └────────────┘
    )" << "\n";
}

void Map::displayAvailableVillagers() const
{
    std::cout << "\n═══════════════════════════════\n";
    std::cout <<   "      Available Villagers            \n";
    std::cout <<   "═══════════════════════════════\n";

    for (const Villager* v : villagers)
    {
        std::string status;
        if (v->get_currentLocation().empty() || v->get_currentLocation() == "none")
        {
            status = "Not on the map yet";
        }else if (v->get_currentLocation() == v->get_safeLocation())
        {
            status = "Reached safe location :)";
        }else 
        {
            status = "En route";
        }
        std::cout << "- " << v->get_name() << " (Current: " << v->get_currentLocation() << ", Safe: " << v->get_safeLocation() << ") --> Status: " << status << "\n";
    }
    std::cout << "═══════════════════════════════\n";
}

void Map::printItems() const 
{
    std::cout << "Items on Map:\n";
    for (const auto& [loc, items] : itemsInLocation) 
    {
        std::cout << loc << ": ";
        for (const auto& item : items)
        {
            std::cout << item.toString() << ", ";
        }
        std::cout << "\n";
    }
}

std::vector<Villager*> Map::get_villagersAt(const std::string& location)
{
    std::vector<Villager*> result;

    for (Villager* v : villagers)
    {
        if (v->get_currentLocation() == location && v->isAlive())
        {
            result.push_back(v);
        }
    }
    return result;
}

std::vector<Hero*> Map::getHeroesAt(const std::string& location)
{
    std::vector<Hero*> result;
    for (const auto& [loc, heroesHere] : heroPositions) {
        if (loc == location) {
            result = heroesHere;
            break;
        }
    }
    return result;
}

void Map::addVillager(Villager* v)
{
    villagers.push_back(v);
}

void Map::setVillagerLocation(Villager* villager , const std::string& location)
{
    if (!villager) return;

    //we remove villager position first
    for (auto& [loc,list] : villagerPositions)
    {
        list.erase(std::remove(list.begin() , list.end() , villager) , list.end());
    }

    //new location
    villagerPositions[location].push_back(villager);
    villager->set_location(location);
}

void Map::placeHero(Hero* hero, const std::string& location)
{
    for (auto& [loc, heroes] : heroPositions)
    {
        heroes.erase(std::remove(heroes.begin(), heroes.end(), hero), heroes.end());
    }

    heroPositions[location].push_back(hero);
}

std::string Map::findNearestHeroLocation(const std::string& from , const std::vector<Hero*> heroes) const
{
    std::queue<std::string> q;
    std::unordered_map<std::string , bool> visited;
    std::unordered_map<std::string , std::string> parent;

    q.push(from);
    visited[from] = true;
    
    while (!q.empty())
    {
        std::string current = q.front();
        q.pop();

        //it checks if a hero is at this location
        auto it = heroPositions.find(current);
        if (it != heroPositions.end() && !it->second.empty())
        {
            return current;
        }

        auto neighborsIt = locationConnections.find(current);
        if (neighborsIt != locationConnections.end())
        {
            for (const std::string& neighbor : neighborsIt->second)
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    parent[neighbor] = current;
                    q.push(neighbor);
                }
            }
        }
    }
    return ""; // it means that 'no hero found'
}

void Map::placeMonster(Monster* monster, const std::string& location)
{
    monster->set_location(location);
    std::cout << "Monster " << monster->get_name() << " placed at " << location << "\n";
}

void Map::moveMonster(Monster* monster , int steps , Dice& dice)
{
    if (!monster || steps <= 0) return;
    std::string currentLocation = monster->get_currentLocation();
    for (int i = 0 ; i < steps ; i++)
    {
        const auto& neighbors = adjacencyList[currentLocation];
        if (neighbors.empty()) break;
        
        //random location
        int r = static_cast<int>(dice.rollOne()) % neighbors.size();
        auto it = neighbors.begin();
        std::advance(it , r);
        currentLocation = *it;
    }

    monster->set_location(currentLocation);
    std::cout << monster->get_name() << " moved to: " << currentLocation << "\n";
}

void Map::monsterStrike(Monster* monster , int strikeCount , const std::vector<Hero*>& heroes , GameController& controller)
{
    std::string monsterLoc = monster->get_currentLocation();

    for (Hero* hero : heroes)
    {
        if (hero->get_location() == monsterLoc)
        {
            hero->receiveDamage(strikeCount);
            std::cout << hero->get_name() << " was attacked by " << monster->get_name() << std::endl;

            if (!hero->isAlive())
            {
                std::cout << hero->get_name() << " has been knocked out!\n";
                controller.increaseTerrorLevel();
            }
        }
    }
}

void Map::manualMoveMonster(Monster* monster)
{
    std::string current = monster->get_currentLocation();
    std::cout << "current location of " << monster->get_name() << ": " << current << "\n";
    std::cout << "connected locations:\n";

    const auto& neighbors = getConnections(current);
    for (const auto& n : neighbors)
    {
        std::cout << "- " << n << "\n";
    }

    std::string destination;
    std::cout << "Enter destination to move the monster: ";
    std::getline(std::cin , destination);

    if (areConnected(current , destination))
    {
        set_characterLocation(monster->get_name() , destination);
        monster->set_location(destination);
        std::cout << monster->get_name() << " moved to " << destination << "\n";
    }else {
        std::cout << "Invalid destination. Movement skipped...\n";
    }
}

void Map::removeVillager(Villager* villager)
{
    if (!villager) return;
    for (auto& [loc,list] : villagerPositions)
    {
        list.erase(std::remove(list.begin() , list.end() , villager) , list.end());
    }
    villagers.erase(std::remove(villagers.begin() , villagers.end() , villager) , villagers.end());
    
    delete villager;
}

Map::~Map()
{
    for (Villager* v : villagers)
    {
        delete v;
    }
    villagers.clear();
}