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
    size(50), posx(posx_), posy(posy_), points(3), color(sf::Color::Magenta), speed(3.0f), 
    type(type_), xBorder(xBorder_), yBorder(yBorder_)
    {
        if(type == 'r')
        {
            triangle.setPointCount(points);
            triangle.setPoint(0,sf::Vector2f(posx, posy));
            triangle.setPoint(1,sf::Vector2f(posx, posy - size));
            triangle.setPoint(2,sf::Vector2f(posx + 100, posy - size / 2));
            triangle.setFillColor(color);
        }
        else if(type == 'l')
        {
            triangle.setPointCount(points);
            triangle.setPoint(0,sf::Vector2f(posx, posy));
            triangle.setPoint(1,sf::Vector2f(posx, posy - size));
            triangle.setPoint(2,sf::Vector2f(posx - 100, posy - size / 2));
            triangle.setFillColor(color);
        }
        else if(type == 'd')
        {
            triangle.setPointCount(points);
            triangle.setPoint(0,sf::Vector2f(posx, posy));
            triangle.setPoint(1,sf::Vector2f(posx - size, posy));
            triangle.setPoint(2,sf::Vector2f(posx - size / 2, posy + 100));
            triangle.setFillColor(color);
        }
        else if(type == 'u')
        {
            triangle.setPointCount(points);
            triangle.setPoint(0,sf::Vector2f(posx, posy));
            triangle.setPoint(1,sf::Vector2f(posx - size, posy));
            triangle.setPoint(2,sf::Vector2f(posx - size / 2, posy - 100));
            triangle.setFillColor(color);
        }
        else if(type == 'a') // is upward left 
        {
            triangle.setPointCount(points);
            triangle.setPoint(0,sf::Vector2f(posx, posy));
            triangle.setPoint(1,sf::Vector2f(posx + size, posy - size / 2));
            triangle.setPoint(2,sf::Vector2f(posx - 100, posy - 100 / 2));
            triangle.setFillColor(sf::Color::Green);

        }
        else if(type == 'b') // is upward Right
        {
            triangle.setPointCount(points);
            triangle.setPoint(0,sf::Vector2f(posx, posy));
            triangle.setPoint(1,sf::Vector2f(posx + size, posy - size / 2));
            triangle.setPoint(2,sf::Vector2f(posx + 100, posy - 100 / 2));
            triangle.setFillColor(sf::Color::Green);

        }
        else if(type == 'c') // is downward left
        {
            triangle.setPointCount(points);
            triangle.setPoint(0,sf::Vector2f(posx, posy));
            triangle.setPoint(1,sf::Vector2f(posx + size / 2, posy + size));
            triangle.setPoint(2,sf::Vector2f(posx - 100, posy + 100 / 2));
            triangle.setFillColor(sf::Color::Green);
        }
        else if(type == 'e') // is downward right
        {
            triangle.setPointCount(points);
            triangle.setPoint(0,sf::Vector2f(posx, posy));
            triangle.setPoint(1,sf::Vector2f(posx + size / 2, posy + size));
            triangle.setPoint(2,sf::Vector2f(posx + 100, posy + 100 / 2));
            triangle.setFillColor(sf::Color::Green);
        }

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
            triangle.setPoint(0,sf::Vector2f(posx, posy));
            triangle.setPoint(1,sf::Vector2f(posx + size, posy - size / 2));
            triangle.setPoint(2,sf::Vector2f(posx - 100, posy - 100 / 2));
        }
        if(type == 'b') // is upward Right
        {
            posx += speed;
            posy -= speed;
            triangle.setPoint(0,sf::Vector2f(posx, posy));
            triangle.setPoint(1,sf::Vector2f(posx + size, posy - size / 2));
            triangle.setPoint(2,sf::Vector2f(posx + 100, posy - 100 / 2));
        }
        if(type == 'c') // is downward left
        {
            posx -= speed;
            posy += speed;
            triangle.setPoint(0,sf::Vector2f(posx, posy));
            triangle.setPoint(1,sf::Vector2f(posx + size / 2, posy + size));
            triangle.setPoint(2,sf::Vector2f(posx - 100, posy + 100 / 2));
        }
        if(type == 'e') // is downward right
        {
            posx += speed;
            posy += speed;
            triangle.setPoint(0,sf::Vector2f(posx, posy));
            triangle.setPoint(1,sf::Vector2f(posx + size / 2, posy + size));
            triangle.setPoint(2,sf::Vector2f(posx + 100, posy + 100 / 2));
        }
        if(type == 'r') 
        {
            posx += speed;
            triangle.setPoint(0,sf::Vector2f(posx, posy));
            triangle.setPoint(1,sf::Vector2f(posx, posy - size));
            triangle.setPoint(2,sf::Vector2f(posx + 100, posy - size / 2));
        }
        if(type == 'l')
        {
            posx -= speed;
            triangle.setPoint(0,sf::Vector2f(posx, posy));
            triangle.setPoint(1,sf::Vector2f(posx, posy - size));
            triangle.setPoint(2,sf::Vector2f(posx - 100, posy - size / 2));
        }
        if(type == 'u')
        {
            posy -= speed;
            triangle.setPoint(0,sf::Vector2f(posx, posy));
            triangle.setPoint(1,sf::Vector2f(posx - size, posy));
            triangle.setPoint(2,sf::Vector2f(posx - size / 2, posy - 100));
        }
        if(type == 'd')
        {
            posy += speed;
            triangle.setPoint(0,sf::Vector2f(posx, posy));
            triangle.setPoint(1,sf::Vector2f(posx - size, posy));
            triangle.setPoint(2,sf::Vector2f(posx - size / 2, posy + 100));
        }
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