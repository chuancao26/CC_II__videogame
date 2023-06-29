#ifndef WORKERBEE_H
#define WORKERBEE_H
#include <SFML/Graphics.hpp>
#include "Enemigos.h"
class WorkerBee : public Enemigo
{
private:
    float life, xSpeed, ySpeed;
    sf::RectangleShape bee;
    sf::Color color;
public:
    // constructor
    WorkerBee(const float& posx_, const float& posy_):
    Enemigo(posx_, posy_, 50), color(sf::Color::Blue), 
    xSpeed(0.2), ySpeed(0.1), life(100) // to define
    {
        bee.setPosition(posx, posy);
        bee.setSize(sf::Vector2f(size, size));
        bee.setFillColor(color);
    }
    void move()
    {
        posx -= xSpeed;
        posy -= ySpeed;
        bee.setPosition(posx, posy);
    }
    void draw(sf::RenderWindow& window)
    {
        move();
        window.draw(bee);
    }
    bool isExpired()
    {
        return (posx <= -size || posy <= -size) ? true : false;
    }
};

#endif 