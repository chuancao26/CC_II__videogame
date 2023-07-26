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

public:
    VistaFlor(sf::RenderWindow& win) : bossController(win),
                                  seed1(win.getSize().x * 2.f / 3.f, win.getSize().y * 2.f / 6.f),
                                  seed2(win.getSize().x * 2.f / 3.f, win.getSize().y * 3.f / 6.f),
                                  seed3(win.getSize().x * 2.f / 3.f, win.getSize().y * 4.f / 6.f)
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        boomerang = new BoomerangController(win.getSize().x * 45 / 64, win.getSize().y / 3, win.getSize().x / 7, win.getSize().y / 10);
        seed1.setDestino(0, 500);
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

    void runMapaFlor(sf::RenderWindow& win)
    {
        float deltaTime = timer.getElapsedTime().asSeconds();

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
            seeds[i]->update();
        }

        bossController.update();
        bossController.draw();

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

// Usage example


// void Mapa1(sf::RenderWindow& window) {
//     std::srand(static_cast<unsigned int>(std::time(nullptr)));
//     BoomerangController *boomerang= new BoomerangController(window.getSize().x * 45 / 64, window.getSize().y / 3, window.getSize().x / 7, window.getSize().y / 10);
//     const int maxBombs = 5;
//     BombController* bombs[maxBombs] = {}; // Arreglo de punteros a CuadradoController
//     float elapsedSeconds = 0.0f;
//     float interval = 1.0f; // Intervalo de tiempo entre la aparición de los cuadrados (1 segundo)

//     //Cuadrado
//     sf::Clock clock;
//     sf::Clock timer; // Reloj para controlar el intervalo de tiempo

// //BOSS
//     BossController bossController(window);
// //SEEDS
//     SeedController seed1(window.getSize().x * 2.f / 3.f, window.getSize().y * 2.f / 6.f);
//     seed1.setDestino(0, 500);
//     SeedController seed2(window.getSize().x * 2.f / 3.f, window.getSize().y * 3.f / 6.f);
//     SeedController seed3(window.getSize().x * 2.f / 3.f, window.getSize().y * 4.f / 6.f);
//     SeedController* seeds[3] = {&seed1, &seed2, &seed3};

//     sf::Clock clockSeed;

//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }
//         // Calcular el tiempo transcurrido desde la última aparición de un cuadrado
//         float deltaTime = timer.getElapsedTime().asSeconds();

//         //sf::Time elapsed = clockSeed.restart();

//         if (deltaTime >= interval) {
//             // Generar una nueva posición aleatoria para el cuadrado
//             float posicionX = static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX) / (window.getSize().x * 3 / 5));

//             // Buscar un espacio disponible en el arreglo de punteros
//             int indice = -1;
//             for (int i = 0; i < maxBombs; i++) {
//                 if (bombs[i] == nullptr) {
//                     indice = i;
//                     //break;
//                 }
//             }

//             // Si se encontró un espacio disponible, crear un nuevo CuadradoController en esa posición
//             if (indice != -1) {
//                 bombs[indice] = new BombController(window.getSize().x, window.getSize().y);
//                 bombs[indice]->update();
//                 bombs[indice]->draw(window);
//             }

//             // Reiniciar el reloj para el siguiente intervalo
//             timer.restart();
//         }
        
//         boomerang[0].update(window.getSize().x);

//         //float deltaTime2 = clock2.restart().asSeconds();
//         //florBoss.update(deltaTime2);

        
//         for (int i = 0; i < 3; ++i) {
//             seeds[i]->update();
//         }

//         //BOSS
//         bossController.update();

//         //SEEDS
//         for (int i = 0; i < 3; ++i) {
//             seeds[i]->update();
//         }
// //CLEAR
//         window.clear();
//         //BOSS
//         bossController.draw();
        
//         if (!boomerang[0].shouldDelete()) {
//             boomerang[0].draw(window);
//         }
//         // Actualizar y dibujar los cuadrados existentes en el arreglo
//         for (int i = 0; i < maxBombs; i++) {
//             if (bombs[i] != nullptr) {
//                 bombs[i]->update();
//                 bombs[i]->draw(window);
//             }
//         }

        
//         for (int i = 0; i < 3; ++i) {
//             seeds[i]->draw(window);
//         }
        

//         //SEEDS
//         for (int i = 0; i < 3; ++i) {
//             //seeds[i]->draw(window);
//            if (!seeds[i]->canDelete()){
//             seeds[i]->draw(window);
//            }
//         }

// //DISPLAY
//         window.display();
//         //if (seed1.canDelete() && seed2.canDelete() && seed3.canDelete()) {
//             // Todos los objetos se pueden eliminar, se sale del bucle
//             //for (int i = 0; i < 3; i++) {
//                 //delete seeds[i];
//             //}
//         //}

//     }

//     for (int i = 0; i < maxBombs; i++) {
//         delete bombs[i];
//     }
//     if (boomerang[0].shouldDelete()==true){
//             delete boomerang;
//         }
//     for (int i = 0; i < 3; i++) {
//                 delete seeds[i];
//             }
// }

#endif
