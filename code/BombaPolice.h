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
#endif


