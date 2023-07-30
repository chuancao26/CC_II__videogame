#ifndef EVENTOSFLOR_H
#define EVENTOSFLOR_H
#include <SFML/Graphics.hpp>
#include "bombcontroller.h"
#include "boomerangcontroller.h"    
#include "seed_controller.h"
#include "bosscreates_controller.h"
#include <vector>
#include <iostream>
#include <ctime>
#include <chrono>
#include <cmath>
#include <string>
#include <memory>
#include "Jugador_Modelo.h"
class VistaFlor
{
private:
    // sf::RenderWindow& window;
    Cup cup1;
    Cup cup2;
    BoomerangController* boomerang;
    const int maxBombs = 5;
    BombController* bombs[5] = {};
    float elapsedSeconds = 0.0f;
    float interval = 1.0f;
    sf::Clock clock;
    sf::Clock timer;
    BossController bossController;
    SeedController seed1;
    SeedController seed2;
    SeedController seed3;
    SeedController* seeds[3] = {&seed1, &seed2, &seed3};
    sf::Clock clockSeed;
    sf::Clock clockBoss;
    float timeSinceLastImageChange;
    float imageChangeInterval; // Default interval, adjust as needed
    sf::Clock timerClock;

public:
    VistaFlor(sf::RenderWindow& win) : bossController(win),
                                  seed1(win.getSize().x * 2.f / 3.f, win.getSize().y * 2.f / 6.f),
                                  seed2(win.getSize().x * 2.f / 3.f, win.getSize().y * 3.f / 6.f),
                                  seed3(win.getSize().x * 2.f / 3.f, win.getSize().y * 4.f / 6.f)
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        boomerang = new BoomerangController(win.getSize().x * 45 / 64, win.getSize().y / 3, win.getSize().x / 7, win.getSize().y / 10);
        seed1.setDestino(0, 500);
        timeSinceLastImageChange = 0.0f;
        imageChangeInterval = 0.042f;
    }
    
    void render(sf::RenderWindow& win)
    {
        runMapaFlor(win);
    }
    ~VistaFlor()
    {
        delete boomerang;
        for (int i = 0; i < maxBombs; i++)
        {
            delete bombs[i];
        }
        for (int i = 0; i < 3; i++)
        {
            delete seeds[i];
        }
    }
    void handleInput(const Cup& cup1_, const Cup& cup2_,sf::RenderWindow& win) 
    {
        cup1 = cup1_;
        cup2 = cup2_;
        runMapaFlor(win);
    }
    void runMapaFlor(sf::RenderWindow& win)
    {
        float deltaTime = timer.getElapsedTime().asSeconds();
        int modo=0;

        if (deltaTime >= interval)
        {
            float posicionX = static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX) / (win.getSize().x * 3 / 5));

            int indice = -1;
            for (int i = 0; i < maxBombs; i++)
            {
                if (bombs[i] == nullptr)
                {
                    indice = i;
                }
            }

            if (indice != -1)
            {
                bombs[indice] = new BombController(win.getSize().x, win.getSize().y);
                bombs[indice]->update();
                bombs[indice]->draw(win);
            }

            timer.restart();
        }

        boomerang[0].update(win.getSize().x);

        for (int i = 0; i < 3; ++i)
        {
            seeds[i]->setDestino(0.f,cup1.getPosy());
            seeds[i]->update();
        }
        
        bossController.setState(3); // Change to the crearObjetosBucle state
        
        float deltaTime3 = timerClock.restart().asSeconds();
        timeSinceLastImageChange += deltaTime3;


        if (timeSinceLastImageChange >= imageChangeInterval) {
            bossController.update(deltaTime3); // Update the controller
            bossController.setState(3);
            timeSinceLastImageChange = 0.0f; // Reset the counter
        }


        if (!boomerang[0].shouldDelete())
        {
            boomerang[0].draw(win);
        }

        for (int i = 0; i < maxBombs; i++)
        {
            if (bombs[i] != nullptr)
            {
                bombs[i]->update();
                bombs[i]->draw(win);
            }
        }

        for (int i = 0; i < 3; ++i)
        {
            seeds[i]->draw(win);
        }

        for (int i = 0; i < 3; ++i)
        {
            if (!seeds[i]->canDelete())
            {
                seeds[i]->draw(win);
            }
        }
        
    }
    
};
#endif 