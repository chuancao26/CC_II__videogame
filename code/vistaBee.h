#ifndef VISTABEE_H
#define VISTABEE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random> 
#include "Police.h"
#include "WorkerBee.h"
#include "Espina.h"
#include "triangulo.h"
#include "MisilBee.h"
class VistaBee
{
private:
    MisilM* misilM;
    MisilV* misilV;
    PoliceM* policeM;
    PoliceV* policeV;
    TrianguloM* triangleM;
    TrianguloV* triangleV;
    WorkerBeeM* workerBeeM;
    WorkerBeeV* workerBeeV;
    bool activeWorker, activeTriangle, activeMisil;
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
        updateMisil();
    }
    bool isOpen()
    {
        return window.isOpen();
    }
    void updateWorker()
    {           
        if(!activeWorker)
        {
            workerBeeM = new WorkerBeeM(xBorder, distributionY(generator));
            workerBeeV = new WorkerBeeV(workerBeeM);
            activeWorker = true;
        }
        if (activeWorker)
        {
            workerBeeM -> move();
            workerBeeV -> move();
            if(workerBeeM -> isExpired())
            {
                delete workerBeeM;
                delete workerBeeV;
                activeWorker = false;
            }
        }
    }
    void updateTriangle()
    {
        if (!activeTriangle)
        {
            triangleM = new TrianguloM(0,0, xBorder, yBorder, 'e');
            triangleV = new TrianguloV(triangleM);
            activeTriangle = true;
        }
        if(activeTriangle)
        {
            triangleM->move();
            triangleV->move();
            if (triangleM->isExpired())
            {
                delete triangleM;
                delete triangleV;
                activeTriangle = false;
            }
        }
    }
    void updateMisil()
    {
        if (!activeMisil)
        {
            misilM = new MisilM(xBorder, yBorder);
            misilV = new MisilV(misilM);
            activeMisil = true;
        }
        if (activeMisil)
        {
            misilM->move();
            misilV->update();
            if (misilM->isExpired())
            {
                delete misilM;
                delete misilV;
                activeMisil = false;
            }
        }
    }
    void drawEntitys()
    {
        drawPolice();
        drawWorker();
        drawTriangle();
        drawMisil();
    }
    void drawMisil()
    {
        if (activeMisil)
        {
            misilV ->draw(window);
        }
    }
    void drawWorker()
    {
        if (activeWorker)
        {
            workerBeeV -> draw(window);
        }
    }
    void drawPolice()
    {
        policeV -> draw(window);
    }
    void drawTriangle()
    {
        if (activeTriangle)
        {
            triangleV -> draw(window);
        }
    }
    ~VistaBee()
    {
        delete workerBeeM;
        delete workerBeeV;
        delete policeM;
        delete policeV;
        delete triangleM;
        delete triangleV;
    }
};
#endif