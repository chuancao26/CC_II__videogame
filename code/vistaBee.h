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
    PoliceM* policeM;
    PoliceV* policeV;
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
        policeM = new PoliceM(xBorder,yBorder);
        policeV = new PoliceV(policeM);
    }
    void render()
    {
        window.clear();
        drawEntitys();
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
        update();
    }
    void update()
    {
        elapsedtime = clock.getElapsedTime();
        policeM ->move();
        policeV -> update(elapsedtime);
        updateTriangle();
        updateWorker();
    }
    bool isOpen()
    {
        return window.isOpen();
    }
    void updateWorker()
    {           
        if(!activeWorker)
        {
            workerBee = new WorkerBee(xBorder, distributionY(generator));
            activeWorker = true;
        }
        if (activeWorker)
        {
            workerBee -> move();
            if(workerBee -> isExpired())
            {
                delete workerBee;
                activeWorker = false;
            }
        }
    }
    void updateTriangle()
    {
        if (!activeTriangle)
        {
            triangle = new Triangulo(0, 0, xBorder, yBorder, 'e');
            activeTriangle = true;
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
    void drawEntitys()
    {
        policeV -> draw(window);
        if (activeWorker)
            workerBee -> draw(window);
        if (activeTriangle)
        {
            triangle -> draw(window);
        }
    }
    ~VistaBee()
    {
        delete workerBee;
        delete policeM;
        delete policeV;
        delete triangle;
    }
};
#endif