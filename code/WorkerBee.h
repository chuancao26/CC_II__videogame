#ifndef WORKERBEE_H
#define WORKERBEE_H
#include <SFML/Graphics.hpp>
#include "Enemigos.h"
#include <memory>
class WorkerBeeM : public Enemigo
{
private:
    float life, xSpeed, ySpeed;
public:
    // constructor
    WorkerBeeM(const float& posx_, const float& posy_):
    Enemigo(posx_, posy_, 50), xSpeed(0.2), ySpeed(0.1), life(100) // to define
    {
    }
    void move()
    {
        posx -= xSpeed;
        posy -= ySpeed;
    }
    void update()
    {
        move();
    }
    bool isExpired()
    {
        return (posx <= -size || posy <= -size) ? true : false;
    }
    float getPosx(){return posx;}
    float getPosy(){return posy;}
    int getSize(){return size;}
};
class WorkerBeeV
{
private:
    std::shared_ptr<WorkerBeeM> wb;
    sf::RectangleShape bee;
    sf::Color color;

public:
    WorkerBeeV(std::shared_ptr<WorkerBeeM> wb_): wb(wb_), color(sf::Color::Blue)
    {
        bee.setPosition(wb ->getPosx(), wb->getPosy());
        bee.setSize(sf::Vector2f(wb ->getSize(), wb ->getSize()));
        bee.setFillColor(color);
    }
    void move()
    {
        bee.setPosition(wb ->getPosx(), wb ->getPosy());
    }
    void draw(sf::RenderWindow& window)
    {
        window.draw(bee);
    }
};
#endif 