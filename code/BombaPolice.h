#ifndef BOMBAPOLICE_H
#define BOMBAPOLICE_H
#include <SFML/Graphics.hpp>
#include <iostream>
class BombaPolice
{
private:
    float posx, posy, lifetime;
    int size;
    sf::CircleShape bomb;
    sf::Clock clock;
    sf::Time elapsedTime;
    sf::Time inicio;
    sf::Color color;
    // sf::RenderWindow window;
public:
    // constructor
    BombaPolice(const float& px, const float& py, sf::Time elapsedTime_): // , const sf::RenderWindow& window_
    posx(px), posy(py), size(50), lifetime(4.0f), color(sf::Color::White), elapsedTime(elapsedTime_),
    inicio(elapsedTime_)
    {
        std::cout << elapsedTime.asSeconds() << " : " << inicio.asSeconds() << std::endl;
        bomb.setPosition(posx, posy);
        bomb.setRadius(size);
        bomb.setFillColor(color);
    }
    void update(sf::Time& deltaTime)
    {
        elapsedTime = deltaTime;
    }
    void draw(sf::RenderWindow& window)
    {
        if (elapsedTime.asSeconds() - inicio.asSeconds() <= lifetime)
        {  
            // std::cout << elapsedTime.asSeconds() << " : " << inicio.asSeconds() << std::endl; 
            window.draw(bomb);
        }
    }
    bool isExpired()
    {
        if (elapsedTime.asSeconds() - inicio.asSeconds() <= lifetime)
        {
            return false;
        }
        return true;
    };
};
class Espina
{
private:
    float posx, posy, speed;
    int size, points;
    sf::ConvexShape triangle;
    sf::Color color;
public:
    // constructor
    Espina(const float& posx_, const float& posy_): size(50), posx(posx_),
    posy(posy_), points(3), color(sf::Color::Magenta), speed(0.2)
    {
        triangle.setPointCount(points);
        triangle.setPoint(0,sf::Vector2f(posx,posy));
        triangle.setPoint(1,sf::Vector2f(posx + size, posy));
        triangle.setPoint(2,sf::Vector2f(posx + size / 2, posy + 100));
        triangle.setFillColor(color);
    }
    void move(const char& type)
    {
        // r is right
        // l is left
        // u is upward
        // d is downward
        if(type == 'r')
        {
            std::cout << "toward the right" << std::endl;
            posx += speed;
        }
        if(type == 'l')
        {
            std::cout << "toward the left" << std::endl;
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
        triangle.setPoint(0,sf::Vector2f(posx,posy));
        triangle.setPoint(1,sf::Vector2f(posx + size, posy));
        triangle.setPoint(2,sf::Vector2f(posx + size / 2, posy + 100));
    }
    void draw(sf::RenderWindow& window)
    {
        window.draw(triangle);
    }
};
#endif


