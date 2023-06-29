#ifndef PINKBALL_H
#define PINKBALL_H
#include <SFML/Graphics.hpp>
#include "Enemigos.h"
#include <iostream>

class PinkBall : public Enemigo
{
private:
    sf::CircleShape ball;
    sf::Color color;
public:
    PinkBall(const float& posx_, const float& posy_): Enemigo(posx_, posy_, 20),
    color(sf::Color::Yellow)
    {
        ball.setFillColor(color);
        ball.setRadius(size);
    }
    void draw()
    {
        
    }
    void move()
    {
        
    }
};
#endif