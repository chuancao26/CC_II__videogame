#ifndef ESPINA_H
#define ESPINA_H
#include <SFML/Graphics.hpp>
class Espina
{
private:
    float posx, posy, speed;
    int size, points, xBorder, yBorder;
    char type;
    sf::ConvexShape triangle;
    sf::Color color;
public:
    // constructor
    Espina(const float& posx_, const float& posy_, const char& type_, const int& xBorder_, const int& yBorder_):
    size(30), posx(posx_), posy(posy_), points(3), color(sf::Color::Magenta), speed(0.5f), 
    type(type_), xBorder(xBorder_), yBorder(yBorder_), triangle(3)
    {
        triangle.setFillColor(color);
        if(type == 'r')
        {
            triangle.setPoint(0,sf::Vector2f(0.0f, 0.0f));
            triangle.setPoint(1,sf::Vector2f(0.0f, 0.0f - size));
            triangle.setPoint(2,sf::Vector2f(0.0f + size, 0.0f - size / 2));
            
        }
        else if(type == 'l')
        {
            triangle.setPoint(0,sf::Vector2f(0.0f, 0.0f));
            triangle.setPoint(1,sf::Vector2f(0.0f, 0.0f - size));
            triangle.setPoint(2,sf::Vector2f(0.0f - size, 0.0f - size / 2));
            
        }
        else if(type == 'd')
        {
            triangle.setPoint(0,sf::Vector2f(0.0f, 0.0f));
            triangle.setPoint(1,sf::Vector2f(0.0f - size, 0.0f));
            triangle.setPoint(2,sf::Vector2f(0.0f - size / 2, 0.0f + size));
            
        }
        else if(type == 'u')
        {
            triangle.setPoint(0,sf::Vector2f(0.0f, 0.0f));
            triangle.setPoint(1,sf::Vector2f(0.0f - size, 0.0f));
            triangle.setPoint(2,sf::Vector2f(0.0f - size / 2, 0.0f - size));
            
        }
        else if(type == 'a') // is upward left 
        {
            triangle.setPoint(0,sf::Vector2f(0.0f, 0.0f));
            triangle.setPoint(1,sf::Vector2f(0.0f + size, 0.0f - size / 2));
            triangle.setPoint(2,sf::Vector2f(0.0f - size, 0.0f - size / 2));
        }
        else if(type == 'b') // is upward Right
        {
            triangle.setPoint(0,sf::Vector2f(0.0f, 0.0f));
            triangle.setPoint(1,sf::Vector2f(0.0f + size, 0.0f + size / 2));
            triangle.setPoint(2,sf::Vector2f(0.0f + size , 0.0f - size));
        }
        else if(type == 'c') // is downward left
        {
            triangle.setPoint(0,sf::Vector2f(0.0f, 0.0f));
            triangle.setPoint(1,sf::Vector2f(0.0f + size / 2, 0.0f + size));
            triangle.setPoint(2,sf::Vector2f(0.0f - size, 0.0f + size / 2));
        }
        else if(type == 'e') // is downward right
        {
            triangle.setPoint(0,sf::Vector2f(0.0f, 0.0f));
            triangle.setPoint(1,sf::Vector2f(0.0f + size / 2, 0.0f + size));
            triangle.setPoint(2,sf::Vector2f(0.0f + size, 0.0f + size / 2));
        }
        triangle.setPosition(posx, posy);
    }
    Espina()
    {
    };
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
        triangle.setPosition(posx, posy);
    }
    void draw(sf::RenderWindow& window)
    {
        window.draw(triangle);
    }
    bool isExpired()
    {
        if (posx <= -size || posy <= -size || posx >= xBorder + size || posy >= yBorder + size )
        {
            return true;
        }
        return false;
    }

};
#endif