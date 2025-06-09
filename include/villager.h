#pragma once 
#include <string>

class Villager
{
private:
    std::string name;
    std::string currentLocation;
    std::string safeLocation;
    bool alive;

public:
    Villager(const std::string& name , const std::string& startLocation , const std::string& safeLocation);

    std::string get_name() const;
    std::string get_currentLocation() const;
    std::string get_safeLocation() const;

    void set_location(const std::string& newLoc);

    bool isAlive() const;
    void kill();
    bool isSafeLocation() const;
};