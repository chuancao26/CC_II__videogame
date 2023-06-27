#ifndef ENEMIGOS_H
#define ENEMIGOS_H
#include <SFML/Graphics.hpp>
class Enemigo
{
public:
    float posx, posy;
    int size;
    Enemigo(const float& posx_, const float& posy_, const int& size_):
    posx(posx_), posy(posy_), size(size_){}
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void move() = 0;
};
#endif