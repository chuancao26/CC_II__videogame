#ifndef BOMBAPOLICE_H
#define BOMBAPOLICE_H
#include <SFML/Graphics.hpp>
#include "Espina.h"
#include "Enemigos.h"
#include <iostream>
#include <memory>
class BombaPoliceM : public Enemigo
{
private:
    float lifetime;
    float elapsedTime;
    float inicio;
public:
    // constructor
    BombaPoliceM(const float& px, const float& py, const float& elapsedTime_):
    Enemigo(px, py, 20), lifetime(2.0f), elapsedTime(elapsedTime_),
    inicio(elapsedTime_)
    {
    }
    void update(const float& deltaTime)
    {
        elapsedTime = deltaTime;
    }
    void move()
    {
        std::cout << "There's no movement" << std::endl;
    }
    bool isExpired()
    {
        if (elapsedTime - inicio <= lifetime)
        {
            return false;
        }
        return true;
    };
    float getPosx() {return posx; }
    float getPosy() {return posy; }
    int getSize() {return size;}
    float getElapsedTime(){return elapsedTime;}
    float getStart(){return inicio;}
    float getLifetime(){return lifetime;}
};
class BombaPoliceV
{
private:
    std::shared_ptr<BombaPoliceM> bombaM;
    sf::CircleShape bomb;
    sf::Clock clock;
    sf::Color color;
public:
    BombaPoliceV(std::shared_ptr<BombaPoliceM> bp):bombaM(bp),color(sf::Color::White)
    {
        bomb.setPosition(bombaM->getPosx(), bombaM->getPosy());
        bomb.setRadius(bombaM->getSize());
        bomb.setFillColor(color);
    }
    void draw(sf::RenderWindow& window)
    {
        if (bombaM->getElapsedTime() - bombaM->getStart() <= bombaM->getLifetime())
        {  
            window.draw(bomb);
        }
    }
};

#endif


