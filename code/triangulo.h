#ifndef TRIANGULO_H
#define TRIANGULO_H
#include <SFML/Graphics.hpp>
#include "Enemigos.h"
#include <iostream>
class Triangulo : public Enemigo
{
private:
    int radius, points, xBorder, yBorder;
    float speed;
    char type;
    sf::ConvexShape triangle;
    sf::Color color;
    sf::Time start;
    sf::Time elapsedTime;
public:
    Triangulo(const float& posx_, const float& posy_, const int& xlimit, const int& ylimit, const char& type_):
    Enemigo(posx_, posy_, 100), points(3), color(sf::Color::White),
    speed(0.1f), xBorder(xlimit), yBorder(ylimit), type(type_)
    {
        triangle.setPointCount(points);
        triangle.setPoint(0,sf::Vector2f(posx, posy));
        triangle.setPoint(1,sf::Vector2f(posx, posy - size));
        triangle.setPoint(2,sf::Vector2f(posx + 100, posy - size / 2));
        triangle.setFillColor(color);
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
        if(type == 'd')
        {
            posx += speed;
            posy += speed;
        }
        triangle.setPoint(0,sf::Vector2f(posx, posy));
        triangle.setPoint(1,sf::Vector2f(posx, posy - size));
        triangle.setPoint(2,sf::Vector2f(posx + 100, posy - size / 2));
    }
    bool isExpired()
    {
        if (posx > xBorder + size || posx < 0 - size || posy > yBorder + size || posy < 0 - size)
            return true;
        return false;
    }
};


#endif