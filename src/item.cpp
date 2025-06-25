#include "item.h"
#include <map>
#include <stdexcept>
#include <sstream>
// const std::map<std::string , std::tuple<Item::Type , int , std::string>> ITEM_DEFENITIONS =
// {"Flower" , {Item::Type::YELLOW , 2 , "Docks"}} ,
// {"Flower" , {Item::Type::YELLOW , 2 , "Docks"}} ,

void Item::moveTo(const std::string& newLocation)
{
    Location = newLocation;
}

Item::Item(const std::string& name  , Type type , int power , const std::string& Location)
: name(name) , type(type) , power(power) , Location(Location) 
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
    return Location;
}

std::string Item::toString() const {
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
        << "Location: " << Location;
    return oss.str();
}