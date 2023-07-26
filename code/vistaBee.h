#ifndef VISTABEE_H
#define VISTABEE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random> 
#include <memory>
#include "Police.h"
#include "WorkerBee.h"
#include "Espina.h"
#include "Triangulo.h"
#include "MisilBee.h"
#include "Textures.h"
#include "Jugador_Modelo.h"
class VistaBee
{
private:
    Cup cup1;
    Cup cup2;
    Textures textures;
    std::shared_ptr<MisilM> misilM;
    std::shared_ptr<MisilV> misilV;
    std::shared_ptr<PoliceM> policeM;
    std::shared_ptr<PoliceV> policeV;
    std::shared_ptr<TrianguloM> triangleM;
    std::shared_ptr<TrianguloV> triangleV;
    std::shared_ptr<WorkerBeeM> workerBeeM;
    std::shared_ptr<WorkerBeeV> workerBeeV;
    bool activeWorker, activeTriangle, activeMisil, cupLeft;
    float rate;
    sf::RenderWindow& window;
    sf::Clock clock;
    float elapsedtime;
    int xBorder, yBorder;
    std::mt19937 generator;
    std::uniform_int_distribution<int> distributionY;
public:
    // constructor
    VistaBee(sf::RenderWindow& window_):
    xBorder(1280), yBorder(720), activeWorker(false), activeTriangle(false), rate(0.0f), window(window_)
    , cupLeft(false) 
    {
        std::random_device rd;
        generator.seed(rd());
        distributionY = std::uniform_int_distribution<int>(150,yBorder);
        // window.create(sf::VideoMode(xBorder, yBorder), windowName);
        policeM = std::make_shared<PoliceM>(xBorder,yBorder);
        policeV = std::make_shared<PoliceV>(policeM, textures.getPoliceTextures(), 
                                            textures.getEspinasTextures(),
                                            textures.getBombTextures());
    }
    void render()
    {
        // window.clear();
        drawEntitys();
        // window.display();
    }
    void handleInput(const Cup& cup1_, const Cup& cup2_) 
    {
        // sf::Event event;
        // while (window.isOpen() && window.pollEvent(event)) 
        // {
        //     if (event.type == sf::Event::Closed)
        //     {
        //         window.close();
        //     }
        // }
        cup1 = cup1_;
        cup2 = cup2_;
        update();
    }
    void update()
    {
        elapsedtime = clock.getElapsedTime().asSeconds();
        policeM ->move();
        policeV -> update(elapsedtime);
        updateTriangle();
        updateWorker();
        updateMisil();
        updatePositionsCup();
    }
    bool isOpen()
    {
        return window.isOpen();
    }
    void updateWorker()
    {     
        if (cupLeft)
        {
            if(!activeWorker)
            {
                workerBeeM = std::make_shared<WorkerBeeM> (xBorder, distributionY(generator),cupLeft);
                workerBeeV = std::make_shared<WorkerBeeV> (workerBeeM, textures.getWorkerTextures());
                activeWorker = true;
            }
            if (activeWorker)
            {
                workerBeeM -> update(elapsedtime);
                workerBeeV -> update();
                if(workerBeeM -> isExpired())
                {
                    workerBeeM.reset();
                    workerBeeV.reset();
                    activeWorker = false;
                }
            }
        }
        else
        {
            if(!activeWorker)
            {
                workerBeeM = std::make_shared<WorkerBeeM> (0, distributionY(generator),cupLeft);
                workerBeeV = std::make_shared<WorkerBeeV> (workerBeeM, textures.getWorkerTextures());
                activeWorker = true;
            }
            if (activeWorker)
            {
                workerBeeM -> update(elapsedtime);
                workerBeeV -> update();
                if(workerBeeM -> isExpired())
                {
                    workerBeeM.reset();
                    workerBeeV.reset();
                    activeWorker = false;
                }
            }
        }


    }
    void updateTriangle()   
    {
        if (!activeTriangle)
        {
            triangleM = std::make_shared<TrianguloM>(0,0, xBorder, yBorder, 'e');
            triangleV = std::make_shared<TrianguloV>(triangleM, textures.getTriangleTextures());
            activeTriangle = true;
        }
        if(activeTriangle)
        {
            triangleM->move();
            triangleV->update(elapsedtime);
            if (triangleM->isExpired())
            {
                triangleM.reset();
                triangleV.reset();
                activeTriangle = false;
            }
        }
    }
    void updateMisil()
    {
        if (!activeMisil)
        {
            misilM = std::make_shared<MisilM>(xBorder, yBorder);
            misilV = std::make_shared<MisilV>(misilM, textures.getMisilBeeTextures());
            activeMisil = true;
        }
        if (activeMisil)
        {
            misilM->update(elapsedtime);
            misilV->update(elapsedtime);
            if (misilM->isExpired())
            {
                misilM.reset();
                misilV.reset();
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
    void updatePositionsCup()
    {
        if (cup1.getPosx() < xBorder / 2)
        {
            cupLeft = true;
        }
        else
        {
            cupLeft = false;
        }
    }
    ~VistaBee()
    {

    }
};
#endif