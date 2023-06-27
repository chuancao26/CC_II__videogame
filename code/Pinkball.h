#ifndef PINKBALL_H
#define PINKBALL_H
#include <SFML/Graphics.hpp>
#include <iostream>
class PinkBall
{
private:
    float posx, posy;
    int size;
    sf::CircleShape ball;
    sf::Color color;
public:
    PinkBall(const float& posx_, const float& posy_): posx(posx_), posy(posy_),
    color(sf::Color::Yellow)
    {
        ball.setFillColor(color);
        ball.setRadius(size);
    }
    void update()
    {

    }
    void draw()
    {

    }
    void move()
    {
        
    }
};
#endif