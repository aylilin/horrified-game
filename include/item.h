#pragma once
#include <string>

class Item
{
public:
    enum class Type {RED , BLUE , YELLOW};
    Item(const std::string& name , Type type , int power , const std::string& Location);

    Type get_type() const;
    int get_power() const;
    const std::string& get_location() const;

    void moveTo(const std::string& newLocation);

    std::string toString() const;  //for showing item info

private:
    std::string name;
    Type type;
    int power;
    std::string Location;
};