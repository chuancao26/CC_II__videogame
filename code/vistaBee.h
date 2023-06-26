#ifndef VISTABEE_H
#define VISTABEE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random> 
#include "Police.h"
#include "WorkerBee.h"
#include "Espina.h"
class VistaBee
{
private:
    Police* police;
    WorkerBee* workerBee;
    bool activeWorker;
    sf::RenderWindow window;
    sf::Clock clock;
    sf::Time elapsedtime;
    int xBorder, yBorder;
    std::string windowName;
    std::mt19937 generator;
    std::uniform_int_distribution<int> distributionY;
public:
    // constructor
    VistaBee():
    xBorder(1680), yBorder(900), windowName("Prueba"), activeWorker(false)
    {
        std::random_device rd;
        generator.seed(rd());
        distributionY = std::uniform_int_distribution<int>(150,yBorder);
        window.create(sf::VideoMode(xBorder, yBorder), windowName);
        police = new Police(xBorder,yBorder);
    }
    void render()
    {
        window.clear();
        police -> draw(window);
        drawWorker();
        if (workerBee)
            workerBee -> draw(window);
        
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
        police -> update(elapsedtime);
        if (workerBee)
        {
            workerBee -> move();
            if(workerBee -> isExpired())
            {
                delete workerBee;
                activeWorker = false;
            }
        }
    }
    bool isOpen()
    {
        return window.isOpen();
    }
    void drawWorker()
    {           
        if(!activeWorker)
        {
            workerBee = new WorkerBee(xBorder, distributionY(generator));
            activeWorker = true;
        }
    }

    ~VistaBee()
    {
        delete workerBee;
        delete police;
    }
};


#endif