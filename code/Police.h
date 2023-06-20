#ifndef POLICE_H
#define POLICE_H
#include <SFML/Graphics.hpp>
#include "BombaPolice.h"
#include <iostream>
class Police
{
private:
    float posx = 1500, posy = 500, life = 100, speed = 1;
    int HeightSize = 200, WidthSize = 200;
    sf::Color color;
    sf::RectangleShape police;
    int xedge, yedge;
    bool movingLeft = false;
    BombaPolice bomba;
    sf::Clock clock;

public:
    Police(const sf::Color& c, const int& limitx, const int& limity)
        : color(c), xedge(limitx), yedge(limity), bomba(posx, posy)
    {
        police.setPosition(posx, posy);
        police.setFillColor(color);
        police.setSize(sf::Vector2f(WidthSize, HeightSize));
    }
    void draw(sf::RenderWindow& window)
    {
        move();
        colocarBomba();
        sf::Time elapsedTime = clock.getElapsedTime();
        bomba.update(elapsedTime);
        bomba.draw(window);
        window.draw(police);
    }
    void move()
    {
        if (movingLeft) {
            posx -= speed;
            if (posx <= 100) {
                movingLeft = false;
            }
        } else {
            posx += speed;
            if (posx >= 1500) {
                movingLeft = true;
            }
        }
        police.setPosition(posx, posy);
    }
    void colocarBomba()
    {
        bomba.setPosicion(posx, posy);
    }
    void print()
    {
        std::cout << bomba.isExpired() << std::endl;
    }
};
#endif
