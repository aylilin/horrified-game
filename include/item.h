#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "locations.h"

class Item
{
public:
    enum class Type {RED , BLUE , YELLOW};
    Item(sf::RenderWindow& window , const sf::Sprite& mapSprite , const std::map<std::string, Position>& locations , std::map<Item::Type , sf::Texture>& itemTextures);

    Type get_type() const;
    int get_power() const;
    const std::string& get_location() const;

    void moveTo(const std::string& newLocation);

    std::string toString() const;  //for showing item info


    const sf::Texture* getTexture() const;
    const sf::Sprite& getSprite() const;

    void setPosition(float x , float y);
    void setScale(float scaleX , float scaleY);

private:
    std::string name;
    Type type;
    int power;
    std::string Location;

    sf::Texture texture;
    sf::Sprite sprite;
};