#ifndef ESPINA_H
#define ESPINA_H
#include <SFML/Graphics.hpp>
#include <iostream>
class EspinaM
{
private:
    float posx, posy, speed;
    int size, xBorder, yBorder;
    char type;
public:
    // constructor
    EspinaM(const float& posx_, const float& posy_, const char& type_, const int& xBorder_, const int& yBorder_):
    size(30), posx(posx_), posy(posy_), speed(0.5f), 
    type(type_), xBorder(xBorder_), yBorder(yBorder_)
    {
    }
    void move()
    {
        // r is right
        // l is left
        // u is upward
        // d is downward
        // a is upward left
        // b is upward right 
        // c is downward left
        // d is downward right
        if(type == 'a') // is upward left 
        {
            
            posx -= speed;
            posy -= speed; 
        }
        if(type == 'b') // is upward Right
        {
            posx += speed;
            posy -= speed;
        }
        if(type == 'c') // is downward left
        {
            posx -= speed;
            posy += speed;
        }
        if(type == 'e') // is downward right
        {
            posx += speed;
            posy += speed;
        }
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
    }
    bool isExpired()
    {
        if (posx <= -size || posy <= -size || posx >= xBorder + size || posy >= yBorder + size )
        {
            return true;
        }
        return false;
    }
    float getPosx(){return posx;}
    float getPosy(){return posy;}
    int getSize(){return size;}
    char getType(){return type;}

};
class EspinaV
{
private:
    EspinaM* e;
    sf::ConvexShape triangle;
    sf::Color color;
public:
    EspinaV(EspinaM*& espina_):
    color(sf::Color::Magenta), triangle(3), e(espina_)
    {
        triangle.setFillColor(color);
        if(e->getType() == 'r')
        {
            triangle.setPoint(0,sf::Vector2f(0.0f, 0.0f));
            triangle.setPoint(1,sf::Vector2f(0.0f, 0.0f - e->getSize()));
            triangle.setPoint(2,sf::Vector2f(0.0f + e->getSize(), 0.0f - e->getSize() / 2));
            
        }
        else if(e->getType() == 'l')
        {
            triangle.setPoint(0,sf::Vector2f(0.0f, 0.0f));
            triangle.setPoint(1,sf::Vector2f(0.0f, 0.0f - e->getSize()));
            triangle.setPoint(2,sf::Vector2f(0.0f - e->getSize(), 0.0f - e->getSize() / 2));
            
        }
        else if(e->getType() == 'd')
        {
            triangle.setPoint(0,sf::Vector2f(0.0f, 0.0f));
            triangle.setPoint(1,sf::Vector2f(0.0f - e->getSize(), 0.0f));
            triangle.setPoint(2,sf::Vector2f(0.0f - e->getSize() / 2, 0.0f + e->getSize()));
            
        }
        else if(e->getType() == 'u')
        {
            triangle.setPoint(0,sf::Vector2f(0.0f, 0.0f));
            triangle.setPoint(1,sf::Vector2f(0.0f - e->getSize(), 0.0f));
            triangle.setPoint(2,sf::Vector2f(0.0f - e->getSize() / 2, 0.0f - e->getSize()));
            
        }
        else if(e->getType() == 'a') // is upward left 
        {
            triangle.setPoint(0,sf::Vector2f(0.0f, 0.0f));
            triangle.setPoint(1,sf::Vector2f(0.0f + e->getSize(), 0.0f - e->getSize() / 2));
            triangle.setPoint(2,sf::Vector2f(0.0f - e->getSize(), 0.0f - e->getSize() / 2));
        }
        else if(e->getType() == 'b') // is upward Right
        {
            triangle.setPoint(0,sf::Vector2f(0.0f, 0.0f));
            triangle.setPoint(1,sf::Vector2f(0.0f + e->getSize(), 0.0f + e->getSize() / 2));
            triangle.setPoint(2,sf::Vector2f(0.0f + e->getSize() , 0.0f - e->getSize()));
        }
        else if(e->getType() == 'c') // is downward left
        {
            triangle.setPoint(0,sf::Vector2f(0.0f, 0.0f));
            triangle.setPoint(1,sf::Vector2f(0.0f + e->getSize() / 2, 0.0f + e->getSize()));
            triangle.setPoint(2,sf::Vector2f(0.0f - e->getSize(), 0.0f + e->getSize() / 2));
        }
        else if(e->getType() == 'e') // is downward right
        {
            triangle.setPoint(0,sf::Vector2f(0.0f, 0.0f));
            triangle.setPoint(1,sf::Vector2f(0.0f + e->getSize() / 2, 0.0f + e->getSize()));
            triangle.setPoint(2,sf::Vector2f(0.0f + e->getSize(), 0.0f + e->getSize() / 2));
        }
        triangle.setPosition(e->getPosx(), e->getPosy());
    }
    void draw(sf::RenderWindow& window)
    {
        window.draw(triangle);
    }
    void move()
    {
        triangle.setPosition(e->getPosx(), e->getPosy());
    }
    void update()
    {
        move();
    }
};
#endif