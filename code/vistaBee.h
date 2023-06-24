#ifndef VISTABEE_H
#define VISTABEE_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Police.h"
#include "WorkerBee.h"
class VistaBee
{
private:
    Police* police;
    WorkerBee* workerBee;
    sf::RenderWindow window;
    sf::Clock clock;
    sf::Time elapsedtime;
    int xBorder, yBorder;
    std::string windowName;
public:
    // constructor
    VistaBee():
    xBorder(1680), yBorder(900), windowName("Prueba") 
    {
        window.create(sf::VideoMode(xBorder, yBorder), windowName);
        police = new Police(xBorder,yBorder);
    }
    void render()
    {
        window.clear();
        police -> draw(window);
        window.display();
    }
    void handleInput() 
    {
        sf::Event event;
        while (window.isOpen() && window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        elapsedtime = clock.getElapsedTime();
        police -> move();
        police -> update(elapsedtime);
    }
    bool isOpen()
    {
        return window.isOpen();
    }
};


#endif