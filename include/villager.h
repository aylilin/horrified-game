#pragma once 
#include <string>

class Villager
{
private:
    std::string name;
    std::string currentLocation;
    std::string safeLocation;
    bool alive;
    bool guided;

public:
    Villager(const std::string& name , const std::string& safeLocation);

    std::string get_name() const;
    std::string get_currentLocation() const;
    std::string get_safeLocation() const;

    void set_location(const std::string& newLoc);
    bool isGuided() const;
    void set_guided(bool);


    bool isAlive() const;
    void kill();
    bool isSafeLocation() const;
};