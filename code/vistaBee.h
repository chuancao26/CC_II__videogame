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

    std::vector<std::shared_ptr<TrianguloM>> triangulosM;    
    std::vector<std::shared_ptr<TrianguloV>> triangulosV;    
    
    std::shared_ptr<WorkerBeeM> workerBeeM;
    std::shared_ptr<WorkerBeeV> workerBeeV;

    bool activeWorker, activeTriangle, activeMisil, cupLeft;
    float rate;
    sf::RenderWindow& window;
    sf::Clock clock;
    float gameTime;
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
        policeM = std::make_shared<PoliceM>(xBorder,yBorder);
        policeV = std::make_shared<PoliceV>(policeM, textures.getPoliceTextures(), 
                                            textures.getEspinasTextures(),
                                            textures.getBombTextures());
    }
    void render()
    {
        drawEntitys();
    }
    void handleInput(const Cup& cup1_, const Cup& cup2_,const float& gameTime_) 
    {
        cup1 = cup1_;
        cup2 = cup2_;
        update();
        gameTime = gameTime_;
    }
    void update()
    {
        updatePolice();
        updateTriangle();
        updateWorker();
        updateMisil();
        updatePositionsCup();
    }
    bool isOpen()
    {
        return window.isOpen();
    }
    void updatePolice()
    {
        if (gameTime <= 30.0f)
        {
            policeM -> move();
            policeV -> update(gameTime);
        }
        else
        {
            policeM.reset();
            policeV.reset();
        }
    }
    void drawPolice()
    {
        if (gameTime <= 30.0f)
        {
            policeV -> draw(window);
        }
    }
    void updateWorker()
    {     
        if (gameTime < 60)
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
                    workerBeeM -> update(gameTime);
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
                    workerBeeM -> update(gameTime);
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

    }
    void drawWorker()
    {
        if (gameTime < 60)
        {
            if (activeWorker)
            {
                workerBeeV -> draw(window);
            }
        }
        
    }
    void updateTriangle()   
    {
        int selector = (distributionY(generator)) % 2 + 1;
        if (!activeTriangle)
        {
            if (selector == 1) // upward and downward
            {
                triangulosM.push_back(std::make_shared<TrianguloM>(xBorder*1/3,yBorder, xBorder, yBorder, 3));
                triangulosM.push_back(std::make_shared<TrianguloM>(xBorder*2/3,0 , xBorder, yBorder, 4));
                for (size_t i{0}; i<triangulosM.size();++i)
                {
                    triangulosV.push_back(std::make_shared<TrianguloV>(triangulosM[i], textures.getTriangleTextures()));
                }
                activeTriangle = true;
            }
            if (selector == 2) // leftward and right ward
            {
                triangulosM.push_back(std::make_shared<TrianguloM>(xBorder, yBorder*1/3, xBorder, yBorder, 2));
                triangulosM.push_back(std::make_shared<TrianguloM>(0, yBorder*2/3, xBorder, yBorder, 1));
                for (size_t i{0}; i<triangulosM.size();++i)
                {
                    triangulosV.push_back(std::make_shared<TrianguloV>(triangulosM[i], textures.getTriangleTextures()));
                }
                activeTriangle = true;
            }
        }
        if(activeTriangle)
        {
            for (size_t i{0}; i<triangulosM.size();++i)
            {
                triangulosM[i]->move();
                triangulosV[i]->update(gameTime);
                if (triangulosM[i]->isExpired())
                {
                    triangulosM[i].reset();
                    triangulosV[i].reset();
                    triangulosM.clear();
                    triangulosV.clear();
                    activeTriangle = false;
                }
            }
        }
    }
    void drawTriangle()
    {
        if (activeTriangle)
        {
            for (size_t i{0}; i<triangulosM.size();++i)
            {
                triangulosV[i]->draw(window);
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
            misilM->update(gameTime);
            misilV->update(gameTime);
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