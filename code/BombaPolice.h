#ifndef BOMBAPOLICE_H
#define BOMBAPOLICE_H
#include <SFML/Graphics.hpp>
#include "Espina.h"
#include "Enemigos.h"
#include <iostream>
class BombaPolice : public Enemigo
{
private:
    float lifetime;
    Espina* espinas;
    sf::CircleShape bomb;
    sf::Clock clock;
    sf::Time elapsedTime;
    sf::Time inicio;
    sf::Color color;
    // sf::RenderWindow window;
public:
    // constructor
    BombaPolice(const float& px, const float& py, sf::Time elapsedTime_):
    Enemigo(px, py, 50), lifetime(5.0f), color(sf::Color::White), elapsedTime(elapsedTime_),
    inicio(elapsedTime_)
    {
        bomb.setPosition(posx, posy);
        bomb.setRadius(size);
        bomb.setFillColor(color);
    }
    void update(sf::Time& deltaTime)
    {
        elapsedTime = deltaTime;
    }
    virtual void draw(sf::RenderWindow& window)
    {
        if (elapsedTime.asSeconds() - inicio.asSeconds() <= lifetime)
        {  
            window.draw(bomb);
        }
    }
    virtual void move()
    {
        std::cout << "There's no movement" << std::endl;
    }
    bool isExpired()
    {
        if (elapsedTime.asSeconds() - inicio.asSeconds() <= lifetime)
        {
            return false;
        }
        return true;
    };
    float getPosx(){return posx; }
    float getPosy(){return posy; }
};
#endif


