#ifndef ESPINA_H
#define ESPINA_H
#include <SFML/Graphics.hpp>
class Espina
{
private:
    float posx, posy, speed;
    int size, points;
    char type;
    sf::ConvexShape triangle;
    sf::Color color;
public:
    // constructor
    Espina(const float& posx_, const float& posy_, const char& type_): size(50), posx(posx_),
    posy(posy_), points(3), color(sf::Color::Magenta), speed(0.5), type(type_)
    {
        if(type == 'r')
        {
            triangle.setPointCount(points);
            triangle.setPoint(0,sf::Vector2f(posx, posy));
            triangle.setPoint(1,sf::Vector2f(posx, posy - size));
            triangle.setPoint(2,sf::Vector2f(posx + 100, posy - size / 2));
            triangle.setFillColor(color);
            std::cout << "entro r" << std::endl;
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
            std::cout << "entro r" << std::endl;
        }
        else if(type == 'u')
        {
            triangle.setPointCount(points);
            triangle.setPoint(0,sf::Vector2f(posx, posy));
            triangle.setPoint(1,sf::Vector2f(posx - size, posy));
            triangle.setPoint(2,sf::Vector2f(posx - size / 2, posy - 100));
            triangle.setFillColor(color);
        }

    }
    void move()
    {
        // r is right
        // l is left
        // u is upward
        // d is downward
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
};
#endif