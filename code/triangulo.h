#ifndef TRIANGULO_H
#define TRIANGULO_H
#include <SFML/Graphics.hpp>
#include "Enemigos.h"
#include <iostream>
class TrianguloM : public Enemigo
{
private:
    int radius, xBorder, yBorder;
    float speed, rotationSpeed;
    char type;
public:
    TrianguloM(const float& posx_, const float& posy_, const int& xlimit, const int& ylimit, const char& type_):
    Enemigo(posx_, posy_, 100), speed(0.01f), xBorder(xlimit), yBorder(ylimit),
    type(type_), rotationSpeed(0.01f)
    {

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
    }
    bool isExpired()
    {
        return (posx > xBorder + size * 2  || posx < 0 - size * 2 || posy > yBorder + size * 2 || posy < 0 - size * 2)? true:false;
    }
    float getPosx(){return posx;}
    float getPosy(){return posy;}
    int getSize(){return size;}
    char getType(){return type;}
    float getRotationSpeed(){return rotationSpeed;}

};

class TrianguloV
{
private:
    TrianguloM* tm;
    sf::ConvexShape triangle;
    sf::Color color;
    sf::Time start;
    sf::Time elapsedTime;
public:
    TrianguloV(TrianguloM*& tm_):tm(tm_), color(sf::Color::White), triangle(3)
    {
        triangle.setPoint(0, sf::Vector2f(0.0f, 0.0f));
        triangle.setPoint(1, sf::Vector2f(0.0f, 100.0f));
        triangle.setPoint(2, sf::Vector2f(100.0f, 50.0f));
        triangle.setFillColor(color);
        triangle.setOrigin(50.0f,50.0f);
        triangle.setPosition(tm->getPosx(), tm->getPosy());
    }
    void draw(sf::RenderWindow& window)
    {
        window.draw(triangle);
    } 
    void move()
    {
        triangle.setRotation(triangle.getRotation() + tm->getRotationSpeed());
        triangle.setPosition(tm->getPosx(), tm->getPosy());
    }
    void update()
    {
        move();
    }
};

#endif