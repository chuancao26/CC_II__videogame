#ifndef VISTABEE_H
#define VISTABEE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random> 
#include "Police.h"
#include "WorkerBee.h"
#include "Espina.h"
#include "triangulo.h"
class VistaBee
{
private:
    Police* police;
    Triangulo* triangle;
    WorkerBee* workerBee;
    bool activeWorker, activeTriangle;
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
    xBorder(1280), yBorder(720), windowName("Prueba"), activeWorker(false), activeTriangle(false)
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
        if (activeWorker)
            workerBee -> draw(window);
        if (activeTriangle)
        {
            triangle -> draw(window);
        }
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
        drawWorker();
        drawTriangle();
        elapsedtime = clock.getElapsedTime();
        police -> update(elapsedtime);
        if (activeWorker)
        {
            workerBee -> move();
            if(workerBee -> isExpired())
            {
                delete workerBee;
                activeWorker = false;
            }
        }
        if(activeTriangle)
        {
            triangle->move();
            if (triangle ->isExpired())
            {
                delete triangle;
                activeTriangle = false;
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
    void drawTriangle()
    {
        if (!activeTriangle)
        {
            triangle = new Triangulo(xBorder * 0.5, yBorder * 0.5, xBorder, yBorder, 'b');
            activeTriangle = true;
        }
    }
    ~VistaBee()
    {
        delete workerBee;
        delete police;
        delete triangle;
    }
};


#endif