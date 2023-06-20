#ifndef PLATAFORMA_H
#define PLATAFORMA_H
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

struct Platform
{
    float x;
    float y;
    float width;
    float height;
    sf::RectangleShape shape;

    sf::FloatRect getGlobalBounds() const;
};

struct Map
{
    public:
    Map parseMap(const std::string& mapString);
    
    std::vector<Platform> platforms;
};
#endif
