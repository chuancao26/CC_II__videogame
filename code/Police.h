#ifndef POLICE_H
#define POLICE_H
#include <SFML/Graphics.hpp>
#include "BombaPolice.h"
#include <iostream>
class Police
{
private:
    float posx, posy, life, speed;
    int HeightSize, WidthSize, xBorder, yBorder;
    bool movingLeft, activeBomb;
    sf::Color color;
    sf::RectangleShape police;
    sf::Clock clock;
    sf::Time elapsedTime;
    BombaPolice* bomb;
    public:
    Police(const int& limitx, const int& limity)
    :posx(1500), posy(500), life(100), speed(0.2),
    WidthSize(200), HeightSize(200),color(sf::Color::Cyan), xBorder(limitx),
    yBorder(limity), movingLeft(false), activeBomb(false)
    {
        police.setPosition(posx, posy);
        police.setFillColor(color);
        police.setSize(sf::Vector2f(WidthSize, HeightSize));
    }
    void move()
    {
        if (movingLeft) {
            posx -= speed;
            if (posx <= 0) {
                movingLeft = false;
            }
        } else {
            posx += speed;
            if (posx >= xBorder) {
                movingLeft = true;
            }
        }
        police.setPosition(posx, posy);
    }
    void colocarBomba(sf::RenderWindow& window)
    {
        if (!activeBomb)
        {
            bomb = new BombaPolice(posx, posy, elapsedTime);
            activeBomb = true;
        }
    }
    void update(sf::Time& timeDelta)
    {
        elapsedTime = timeDelta;
        if(bomb)
        {
            bomb -> update(timeDelta);
            if (bomb->isExpired())
            {
                activeBomb = false;
                delete bomb;
            }
        }
    }
    void draw(sf::RenderWindow& window)
    {
        move();
        colocarBomba(window);
        if (bomb)
        {
            bomb->draw(window);
        }
        window.draw(police);
    }
    ~Police()
    {
        delete bomb;
    }
};
#endif
