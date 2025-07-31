#include "../include/hero.h"
#include "../include/itemBag.h"
#include "../include/monster.h"
#include "../include/map.h"
#include "../include/perkCard.h"

#include <iostream>
#include <stdexcept>

Hero::Hero(const std::string& name , int actions , const std::string& startLocation) 
: name(name) , actions(actions) , remainingActions(actions) , currentLocation(startLocation) 
{
    if (actions <= 0)
    {
        throw std::invalid_argument("number of actions must be positive!");
    }

    if (name.empty())
    {
        throw std::invalid_argument("hero's name could not be empty!");
    }
}

void Hero::move(const std::string& newLocation)
{
    if (remainingActions <= 0)
    {
        throw std::runtime_error("there is not enough action...");
    }

    if (newLocation.empty())
    {
        throw std::invalid_argument("location is not valid...");
    }
    
    currentLocation = newLocation;
    remainingActions--;
    std::cout << name  << " moved to " << newLocation << std::endl;
}

void Hero::pickup(ItemBag& bag)
{
    if (remainingActions <= 0)
    {
        std::cout << "Not enough actions to pick up item.\n";
        return;
    }

    bool success = bag.transferItemToHero(currentLocation , *this);
    if (success)
    {
        remainingActions--;
        std::cout << name << " picked up item at " << currentLocation << "\n";
    } else {
        std::cout << "No such item at your location.\n";
    }
}

void Hero::dropAllItems(ItemBag& bag)
{
    for (const Item& item : inventory)
    {
        Item dropped = item;
        dropped.moveTo(currentLocation);
        bag.addItem(dropped);
    }
    inventory.clear();
    std::cout << name << " dropped all items at " << currentLocation << "\n";
}

void Hero::guide(Map& map)
{
    if (remainingActions <= 0)
    {
        std::cout << "Not enough actions to guide.\n";
        return;
    }

    std::vector<Villager*> villagers = map.get_villagersAt(currentLocation);
    if (villagers.empty())
    {
        std::cout << "No villagers to guide at this location.\n";
        return;
    }

    std::cout << "Villagers at " << currentLocation << ":\n";
    for (size_t i = 0; i < villagers.size(); ++i)
    {
        std::cout << i + 1 << ". " << villagers[i]->get_name() << "\n";
    }

    int choice = 1;
    if (villagers.size() > 1)
    {
        std::cout << "Enter number of villager to guide: ";
        std::cin >> choice;
        std::cin.ignore();
    }

    if (choice < 1 || choice > villagers.size())
    {
        std::cout << "Invalid choice.\n";
        return;
    }

    Villager* selected = villagers[choice - 1];

    std::cout << "Guiding " << selected->get_name() << " along with hero.\n";

    map.markVillagerAsGuided(selected->get_name());

    remainingActions--;
}

void Hero::addExtraActions(int count) 
{
    extraActions += count;
}

void Hero::resetActions() 
{
    remainingActions = actions + extraActions;
    extraActions = 0;
}

void Hero::addItem(const Item& item)
{
    inventory.push_back(item);
}

const std::vector<Item>& Hero::get_inventory() const
{
    return inventory;
}

void Hero::set_location(const std::string& newLocation) 
{
    currentLocation = newLocation;
}

void Hero::receiveDamage(int amount)
{
    health -= amount;
    if (health <= 0) health = 0;
    std::cout << name << "Damaged....(health : " << health << ")\n";
}

void Hero::givePerk(std::unique_ptr<PerkCard> newPerk)
{
    perk = std::move(newPerk);
}

bool Hero::hasPerk() const
{
    return perk != nullptr;
}

void Hero::usePerk(Map& map, std::vector<Hero*>& heroes, std::vector<Monster*>& monsters, ItemBag& bag, bool& skipMonsterPhase)
{
    if (!hasPerk())
    {
        std::cout << "No perk card to use.\n";
        return;
    }

    perk->apply(*this, heroes, monsters, bag, map, skipMonsterPhase);
    std::cout << "Perk card used: " << perk->get_name() << "\n";
    perk.reset();
}

std::string Hero::get_name() const
{
    return name;
}

int Hero::get_health() const
{
    return health;
}

int Hero::get_remainingActions() const
{
    return remainingActions;
}

bool Hero::isAlive() const
{
    return health > 0;
}

std::string Hero::get_location() const
{
    return currentLocation;
}
