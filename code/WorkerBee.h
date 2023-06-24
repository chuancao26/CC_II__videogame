#ifndef WORKERBEE_H
#define WORKERBEE_H
#include <SFML/Graphics.hpp>
class WorkerBee
{
private:
    float posx, posy, life, xSpeed, ySpeed;
    int size;
    sf::RectangleShape bee;
    sf::Color color;
public:
    // constructor
    WorkerBee(const float& posx_, const float& posy_):
    posx(posx_), posy(posy_), size(100), color(sf::Color::Blue), 
    xSpeed(0.3), ySpeed(0.1), life(100) // to define
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
};

#endif 