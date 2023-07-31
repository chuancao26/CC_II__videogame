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
#include "Bala.cpp"

class VistaFlor
{
private:
    Cup cup1;
    Cup cup2;
    BoomerangController* boomerang;
    const int maxBombs = 5;
    BombController* bombs[5] = {};
    float elapsedSeconds = 0.0f;
    float interval = 1.0f;
    sf::Clock clock;
    float deltaTime;
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
    float deltatime;
    float bombTimers[5] = {};

    sf::FloatRect jugador1;
    sf::FloatRect jugador2;
    std::mt19937 generator;
    std::uniform_int_distribution<int> distributionY;

    // Flags to track if certain actions have been performed
    bool updateOnceInRange45 = true;
    bool updateOnceInRange35 = true;
    bool updateOnceInRange25 = true;

    BalaNormalVista balaVista;
public:
    VistaFlor(sf::RenderWindow& win) : bossController(win),
                                  seed1(win.getSize().x * 2.f / 3.f, win.getSize().y * 2.f / 6.f),
                                  seed2(win.getSize().x * 2.f / 3.f, win.getSize().y * 3.f / 6.f),
                                  seed3(win.getSize().x * 2.f / 3.f, win.getSize().y * 4.f / 6.f)
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        boomerang = new BoomerangController(win.getSize().x * 45 / 64, win.getSize().y / 3, win.getSize().x / 7, win.getSize().y / 10);
        seed1.setDestino(0, 500);
        deltatime = timer.getElapsedTime().asSeconds();
        deltaTime = clock.getElapsedTime().asSeconds();
    }
    
    void render(sf::RenderWindow& win)
    {
        //runMapaFlor(win);
        draw(win);
    }

    void handleInput(sf::RenderWindow& win, const Cup& cup1_, const Cup& cup2_,
                     const sf::Sprite& player1, const sf::Sprite& player2) 
    {
        cup1 = cup1_;
        cup2 = cup2_;
        jugador1 = player1.getGlobalBounds();
        jugador2 = player2.getGlobalBounds();
        update(win);
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

    void update(sf::RenderWindow& win)
    {
        // Update all objects
        updateBoomerang(win);
        updateSeeds();
        bossController.update();
        updateBombs(win,deltatime);
        //updateBalaVista(win); // Actualizar la posición de la bala
        //checkBulletCollisionWithBoss(win); // Verificar colisión entre la bala y el boss
        colisionesPlayer1Flor();
        colisionesPlayer2Flor();
    }

    void draw(sf::RenderWindow& win)
    {
        drawBoomerang(win);
        drawSeeds(win);
        bossController.draw();
        drawBombs(win);
    }

    void updateBoomerang(sf::RenderWindow& win)
    {
        boomerang[0].update(win.getSize().x);
    }

    void updateSeeds()
    {
        for (int i = 0; i < 3; ++i)
        {
            seeds[i]->setDestino(0.f,cup1.getPosy());
            seeds[i]->update();
        }
    }
    
    void updateBombs(sf::RenderWindow& win, float deltaTime)
    {
        elapsedSeconds += deltaTime; // Incrementar el tiempo transcurrido

        // Actualizar los temporizadores de cada bomba
        for (int i = 0; i < maxBombs; i++)
        {
            if (bombs[i] != nullptr)
            {
                bombTimers[i] += deltaTime;
            }
        }

        // Verificar si ha pasado el tiempo suficiente para crear la siguiente bomba
        if (elapsedSeconds >= interval)
        {
            // Buscar la siguiente bomba disponible en el arreglo
            int nextAvailableBomb = -1;
            for (int i = 0; i < maxBombs; i++)
            {
                if (bombs[i] == nullptr)
                {
                    nextAvailableBomb = i;
                    break;
                }
            }

            // Si hay una bomba disponible, crearla y reiniciar el temporizador
            if (nextAvailableBomb != -1)
            {
                bombs[nextAvailableBomb] = new BombController(win.getSize().x, win.getSize().y);
                bombTimers[nextAvailableBomb] = 0.0f;
            }

            // Reiniciar el temporizador global para la siguiente bomba
            elapsedSeconds = 0.0f;
        }

        // Actualizar las bombas que han pasado su tiempo de intervalo
        for (int i = 0; i < maxBombs; i++)
        {
            if (bombs[i] != nullptr && bombTimers[i] >= i * interval)
            {
                bombs[i]->update();
            }
        }

        // Obtener el rango de vida actual del boss
        int vidaBoss = bossController.getvida();

        // Realizar acciones según el rango de vida del boss
        if (vidaBoss > 40 && vidaBoss < 45 && updateOnceInRange45)
        {
            bossController.setState(3);
            boomerang[0].update(win.getSize().x);
            updateSeeds();
            updateOnceInRange45 = false; // Marcar como actualizado para que no se repita
        }
        else if (vidaBoss > 30 && vidaBoss < 35 && updateOnceInRange35)
        {
            bossController.setState(3);
            boomerang[0].update(win.getSize().x);
            updateSeeds();
            updateBombs(win, deltatime); // Actualizar los objetos bombs
            updateOnceInRange35 = false; // Marcar como actualizado para que no se repita
        }
        else if (vidaBoss > 20 && vidaBoss < 25 && updateOnceInRange25)
        {
            bossController.setState(4);
            updateOnceInRange25 = false; // Marcar como actualizado para que no se repita
        }
    }

    // Draw individual objects
    void drawBoomerang(sf::RenderWindow& win)
    {
        if (!boomerang[0].shouldDelete())
        {
            boomerang[0].draw(win);
        }
    }

    void drawSeeds(sf::RenderWindow& win)
    {
        for (int i = 0; i < 3; ++i)
        {
            seeds[i]->draw(win);
        }
    }

    void drawBombs(sf::RenderWindow& window)
    {
        for (int i = 0; i < maxBombs; i++)
        {
            if (bombs[i] != nullptr)
            {
                bombs[i]->draw(window);
            }
        }
    }

    void colisionesPlayer1Flor()
    {
         float cutPix = 2.0f; 
        // Colisiones con boomerang
        if (!boomerang[0].shouldDelete())
        {
            sf::FloatRect entityBounds(boomerang[0].getSprite().getPosition(),
                                       sf::Vector2f(boomerang[0].getSprite().getGlobalBounds().width - cutPix,
                                                    boomerang[0].getSprite().getGlobalBounds().height - cutPix));
            cup1.enChoque(jugador1.intersects(entityBounds));
        }

        // Colisiones con semillas
        for (int i = 0; i < 3; ++i)
        {
            sf::FloatRect entityBounds(seeds[i]->getSprite().getPosition(),
                                       sf::Vector2f(seeds[i]->getSprite().getGlobalBounds().width - cutPix,
                                                    seeds[i]->getSprite().getGlobalBounds().height - cutPix));
            cup1.enChoque(jugador1.intersects(entityBounds));
        }
        
    }

    void colisionesPlayer2Flor()
    {
         float cutPix = 2.0f; 
        // Colisiones con boomerang
        if (!boomerang[0].shouldDelete())
        {
            sf::FloatRect entityBounds(boomerang[0].getSprite().getPosition(),
                                       sf::Vector2f(boomerang[0].getSprite().getGlobalBounds().width - cutPix,
                                                    boomerang[0].getSprite().getGlobalBounds().height - cutPix));
            cup2.enChoque(jugador2.intersects(entityBounds));
        }

        // Colisiones con semillas
        for (int i = 0; i < 3; ++i)
        {
            sf::FloatRect entityBounds(seeds[i]->getSprite().getPosition(),
                                       sf::Vector2f(seeds[i]->getSprite().getGlobalBounds().width - cutPix,
                                                    seeds[i]->getSprite().getGlobalBounds().height - cutPix));
            cup2.enChoque(jugador2.intersects(entityBounds));
        }

    }
    void updateBalaVista(sf::RenderWindow& win)
    {
        balaVista.setPosition(balaVista.posx, balaVista.posy);
    }

    void checkBulletCollisionWithBoss(sf::RenderWindow& win)
    {
        // Obtener el rango de vida actual del boss
        int vidaBoss = bossController.getvida();
        float tolerance = 5.0f;

        // Verificar colisión entre el sprite de la bala y la línea del boss
        if (balaVista.get().getPosition().x >= bossController.lineX() - tolerance)
        {
            // Generar colisión
            std::cout << "Ataque" << std::endl;
            bossController.Attack();
        }
    }
};

#endif
