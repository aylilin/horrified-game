#include "item.h"
#include <map>
#include <stdexcept>
#include <sstream>

void Item::moveTo(const std::string& newLocation)
{
    location = newLocation;
}

Item::Item(const std::string& name , Type type , int power , const std::string& location) : name(name) , type(type) , power(power) , location(location)
{
    if (name.empty())
    {
        throw std::invalid_argument("Item name cannot be empty!");
    }

    if (power < 1 || power > 6)
    {
        throw std::invalid_argument("Power must be 1-6...");
    }
}

Item::Item(sf::RenderWindow& window , const sf::Sprite& mapSprite , const std::map<std::string , Position>& locations , std::map<Item::Type , sf::Texture>& itemTextures) {}


Item::Type Item::get_type() const 
{
    return type;
}

int Item::get_power() const
{
    return power;
}

const std::string& Item::get_location() const
{
    return location;
}

std::string Item::toString() const
{
    std::ostringstream oss;
    std::string typeStr;
    switch (type) {
        case Type::RED: typeStr = "Red"; break;
        case Type::BLUE: typeStr = "Blue"; break;
        case Type::YELLOW: typeStr = "Yellow"; break;
    }

    oss << "[" << name << "] "
        << "Type: " << typeStr << ", "
        << "Power: " << power << ", "
        << "Location: " << location;
    return oss.str();
}