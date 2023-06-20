#ifndef PLATAFORMA_H
#define PLATAFORMA_H
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

class Platform
{
    public:
    float x;
    float y;
    float width;
    float height;
    sf::RectangleShape shape;
    public:
    sf::FloatRect getGlobalBounds() const;
};

class Map
{
    public:
    Map parseMap(const std::vector<std::string>& mapStrings);
    public:
    std::vector<Platform> platforms;
};
#endif
