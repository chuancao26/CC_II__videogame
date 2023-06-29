#ifndef TRIANGULO_H
#define TRIANGULO_H
#include <SFML/Graphics.hpp>
#include "Enemigos.h"
#include <iostream>
class Triangulo : public Enemigo
{
private:
    int radius, points, xBorder, yBorder;
    float speed, rotationSpeed;
    char type;
    sf::ConvexShape triangle;
    sf::Color color;
    sf::Time start;
    sf::Time elapsedTime;
public:
    Triangulo(const float& posx_, const float& posy_, const int& xlimit, const int& ylimit, const char& type_):
    Enemigo(posx_, posy_, 100), points(3), color(sf::Color::White),
    speed(0.01f), xBorder(xlimit), yBorder(ylimit), type(type_), rotationSpeed(0.01f), triangle(3)
    {
        triangle.setPoint(0, sf::Vector2f(0.0f, 0.0f));
        triangle.setPoint(1, sf::Vector2f(0.0f, 100.0f));
        triangle.setPoint(2, sf::Vector2f(100.0f, 50.0f));
        triangle.setFillColor(color);
        triangle.setOrigin(50.0f,50.0f);
        triangle.setPosition(posx, posy);
    } 
    virtual void draw(sf::RenderWindow& window)
    {
        window.draw(triangle);
    } 
    virtual void move()
    {
        if(type == 'r')
        {
            posx += speed;
        }
        if(type == 'l')
        {
            posx -= speed;
        }
        if(type == 'u')
        {
            posy -= speed;
        }
        if(type == 'd')
        {
            posy += speed;
        }
        if(type == 'a')
        {
            posx -= speed;
            posy -= speed;
        }
        if(type == 'b')
        {
            posx += speed;
            posy -= speed;
        }
        if(type == 'c')
        {
            posx -= speed;
            posy += speed;
        }
        if(type == 'e')
        {
            posx += speed;
            posy += speed;
        }
        triangle.setRotation(triangle.getRotation() + rotationSpeed);
        triangle.setPosition(posx,posy);
    }
    bool isExpired()
    {
        if (posx > xBorder + size * 2  || posx < 0 - size * 2 || posy > yBorder + size * 2 || posy < 0 - size * 2)
            return true;
        return false;
    }
};


#endif