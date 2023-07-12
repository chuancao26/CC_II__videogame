#ifndef VISTABEE_H
#define VISTABEE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random> 
#include <memory>
#include "Police.h"
#include "WorkerBee.h"
#include "Espina.h"
#include "triangulo.h"
class VistaBee
{
private:
    std::shared_ptr<PoliceM> policeM;
    std::shared_ptr<PoliceV> policeV;
    std::shared_ptr<TrianguloM> triangleM;
    std::shared_ptr<TrianguloV> triangleV;
    std::shared_ptr<WorkerBeeM> workerBeeM;
    std::shared_ptr<WorkerBeeV> workerBeeV;
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
        policeM = std::make_shared<PoliceM>(xBorder,yBorder);
        policeV = std::make_shared<PoliceV>(policeM);
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
            workerBeeM = std::make_shared<WorkerBeeM> (xBorder, distributionY(generator));
            workerBeeV = std::make_shared<WorkerBeeV> (workerBeeM);
            activeWorker = true;
        }
        if (activeWorker)
        {
            workerBeeM -> move();
            workerBeeV -> move();
            if(workerBeeM -> isExpired())
            {
                workerBeeM.reset();
                workerBeeV.reset();
                activeWorker = false;
            }
        }
    }
    void updateTriangle()
    {
        if (!activeTriangle)
        {
            triangleM = std::make_shared<TrianguloM>(0,0, xBorder, yBorder, 'e');
            triangleV = std::make_shared<TrianguloV>(triangleM);
            activeTriangle = true;
        }
        if(activeTriangle)
        {
            triangleM->move();
            triangleV->move();
            if (triangleM->isExpired())
            {
                triangleM.reset();
                triangleV.reset();
                activeTriangle = false;
            }
        }
    }
    void drawEntitys()
    {
        policeV -> draw(window);
        if (activeWorker)
        {
            workerBeeV -> draw(window);
        }
        if (activeTriangle)
        {
            triangleV -> draw(window);
        }
    }
    ~VistaBee()
    {

    }
};
#endif