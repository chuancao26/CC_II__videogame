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

    std::vector<std::shared_ptr<MisilM>> misilesM;
    std::vector<std::shared_ptr<MisilV>> misilesV;

    std::shared_ptr<PoliceM> policeM;
    std::shared_ptr<PoliceV> policeV;
    std::vector<std::shared_ptr<TrianguloM>> triangulosM;    
    std::vector<std::shared_ptr<TrianguloV>> triangulosV;    
    
    std::shared_ptr<WorkerBeeM> workerBeeM;
    std::shared_ptr<WorkerBeeV> workerBeeV;

    sf::FloatRect jugadorBounds1;
    sf::FloatRect jugadorBounds2;
    bool activeWorker, activeTriangle, activeMisil, cupLeft;
    float rate;
    sf::RenderWindow& window;
    sf::Clock clock;
    float gameTime;
    int xBorder, yBorder, cutPix;
    std::mt19937 generator;
    std::uniform_int_distribution<int> distributionY;
public:
    // constructor
    VistaBee(sf::RenderWindow& window_):
    xBorder(1280), yBorder(720), activeWorker(false), activeTriangle(false), rate(0.0f), window(window_)
    , cupLeft(false), cutPix(10)
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
    void handleInput(const Cup& cup1_, const Cup& cup2_,const float& gameTime_,
                     const sf::Sprite& player, const sf::Sprite& player2) 
    {
        cup1 = cup1_;
        cup2 = cup2_;
        jugadorBounds1 = player.getGlobalBounds();
        jugadorBounds2 = player2.getGlobalBounds();
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
        colisionesPlayer1Bee();
        colisionesPlayer2Bee();
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
        if (gameTime < 10)
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
        else 
            activeWorker = false;

    }
    void drawWorker()
    {
        if (gameTime < 60 && activeWorker)
        {
            workerBeeV -> draw(window);
        }
    }
    void updateTriangle()   
    {
        if (gameTime > 30 && gameTime < 90)
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
        else
        {
            activeTriangle = false;
        }
    }
    void drawTriangle()
    {
        if (activeTriangle && gameTime > 30 && gameTime < 90)
        {
            for (size_t i{0}; i<triangulosM.size();++i)
            {
                triangulosV[i]->draw(window);
            }
        }
    }
    void updateMisil()
    {
        if (gameTime > 30 && gameTime < 90)
        {
            if (!activeMisil)
            {
                
                misilesM.push_back(std::make_shared<MisilM>(xBorder, yBorder,1));
                misilesM.push_back(std::make_shared<MisilM>(xBorder, yBorder,2));
                for (size_t i{0}; i<misilesM.size();++i)
                {
                    misilesV.push_back(std::make_shared<MisilV>(misilesM[i], textures.getMisilBeeTextures()));
                }
                activeMisil = true;
            }
            if (activeMisil)
            {
                for (size_t i{0}; i<misilesM.size();++i)
                {
                    misilesM[i]->update(gameTime);
                    misilesV[i]->update(gameTime);
                    if (misilesM[i]->isExpired())
                    {
                        misilesM[i].reset();
                        misilesV[i].reset();
                        misilesM.clear();
                        misilesV.clear();
                        activeMisil = false;
                    }
                }

            }
        }
        else
        {
            activeMisil = false;
        }
    }
    void drawMisil()
    {
        if (activeMisil && gameTime > 30 && gameTime < 90)
        {     
            for (size_t i{0}; i<misilesM.size();++i)
            {
                misilesV[i]->draw(window);
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
    void colisionesPlayer1Bee()
    {
        //worker 
        if(activeWorker)
        {
            sf::FloatRect entityBounds(workerBeeV->getSprite().getPosition(),
                                        sf::Vector2f(workerBeeV->getSprite().getGlobalBounds().width - cutPix,
                                        workerBeeV->getSprite().getGlobalBounds().height - cutPix));
            cup1.enChoque(jugadorBounds1.intersects(entityBounds));
        }
        //triangles
        if (activeTriangle)
        {
            for (size_t i{0};i < triangulosV.size(); ++i)
            {   
                sf::FloatRect entityBounds(triangulosV[i]->getSprite().getPosition(),
                            sf::Vector2f(triangulosV[i]->getSprite().getGlobalBounds().width - cutPix,
                            triangulosV[i]->getSprite().getGlobalBounds().height - cutPix));
                cup1.enChoque(jugadorBounds1.intersects(entityBounds));    
            }
        }
        //misil
        if (activeMisil)
        {
            for (size_t i{0};i < misilesV.size(); ++i)
            {   
                sf::FloatRect entityBounds(misilesV[i]->getSprite().getPosition(),
                            sf::Vector2f(misilesV[i]->getSprite().getGlobalBounds().width - cutPix,
                            misilesV[i]->getSprite().getGlobalBounds().height - cutPix));
                cup1.enChoque(jugadorBounds1.intersects(entityBounds));    
            }
        }
        if (policeV.use_count() > 0)
        {
            sf::FloatRect entityBounds(policeV->getSprite().getPosition(),
                        sf::Vector2f(policeV->getSprite().getGlobalBounds().width - cutPix,
                        policeV->getSprite().getGlobalBounds().height - cutPix));
            cup1.enChoque(jugadorBounds1.intersects(entityBounds));
            if (policeV->getActiveBomb())
            {
                if (policeV->getActiveEspinas())
                {
                    for(size_t i{0}; policeV->getEspinasV().size(); ++i)
                    {
                        sf::FloatRect entityBounds(policeV->getEspinasV()[i]->getSprite().getPosition(),
                                    sf::Vector2f(policeV->getEspinasV()[i]->getSprite().getGlobalBounds().width - cutPix,
                        policeV->getEspinasV()[i]->getSprite().getGlobalBounds().height - cutPix));
                        cup1.enChoque(jugadorBounds1.intersects(entityBounds)); 
                    }
                }
            }
            
        }
        
    }
    void colisionesPlayer2Bee()
    {
        //worker 
        if(activeWorker)
        {
            sf::FloatRect entityBounds(workerBeeV->getSprite().getPosition(),
                                        sf::Vector2f(workerBeeV->getSprite().getGlobalBounds().width - cutPix,
                                        workerBeeV->getSprite().getGlobalBounds().height - cutPix));
            cup2.enChoque(jugadorBounds2.intersects(entityBounds));
        }
        //triangles
        if (activeTriangle)
        {
            for (size_t i{0};i < triangulosV.size(); ++i)
            {   
                sf::FloatRect entityBounds(triangulosV[i]->getSprite().getPosition(),
                            sf::Vector2f(triangulosV[i]->getSprite().getGlobalBounds().width - cutPix,
                            triangulosV[i]->getSprite().getGlobalBounds().height - cutPix));
                cup2.enChoque(jugadorBounds2.intersects(entityBounds)); 
                std::cout << triangulosV[i]->getSprite().getGlobalBounds().width - cutPix << std::endl;
            }
        }
        //misil
        if (activeMisil)
        {
            for (size_t i{0};i < misilesV.size(); ++i)
            {   
                sf::FloatRect entityBounds(misilesV[i]->getSprite().getPosition(),
                            sf::Vector2f(misilesV[i]->getSprite().getGlobalBounds().width - cutPix,
                            misilesV[i]->getSprite().getGlobalBounds().height - cutPix));
                cup2.enChoque(jugadorBounds2.intersects(entityBounds));    
            }
        }
        // police
        if (policeV.use_count() > 0)
        {
            sf::FloatRect entityBounds(policeV->getSprite().getPosition(),
                        sf::Vector2f(policeV->getSprite().getGlobalBounds().width - cutPix,
                        policeV->getSprite().getGlobalBounds().height - cutPix));
            cup2.enChoque(jugadorBounds2.intersects(entityBounds));
            // Espinas
            if (policeV->getActiveBomb())
            {
                if (policeV->getActiveEspinas())
                {
                    for(size_t i{0}; policeV->getEspinasV().size(); ++i)
                    {
                        sf::FloatRect entityBounds(policeV->getEspinasV()[i]->getSprite().getPosition(),
                                    sf::Vector2f(policeV->getEspinasV()[i]->getSprite().getGlobalBounds().width - cutPix,
                        policeV->getEspinasV()[i]->getSprite().getGlobalBounds().height - cutPix));
                        cup2.enChoque(jugadorBounds2.intersects(entityBounds)); 
                    }
                }
            }
        }

    }

    ~VistaBee()
    {

    }
};
#endif