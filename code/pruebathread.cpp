#include <SFML/Graphics.hpp>
#include <thread>
#include <atomic>
#include <iostream>
#include <memory>
#include "Cup.h"
#include "Textures.h"
#include "FlyingFist.h"
#include <cmath>


// ... (Asumiendo que aquí se encuentran las definiciones de las clases FlyingFistM, FlyingFistV, Textures, CupHeadM y CupHeadV)

int main()
{
    Textures textures;
    std::shared_ptr<CupHeadM> cupM = std::make_shared<CupHeadM>(400, 400, 800, 800);
    std::shared_ptr<CupHeadV> cupV = std::make_shared<CupHeadV>(cupM, textures.getRedRunTextures(),
                                                                textures.getRedJumpTextures(),
                                                                textures.getRedStandingTextures());

    std::shared_ptr<CupHeadM> cupM2 = std::make_shared<CupHeadM>(500, 500, 800, 800);
    std::shared_ptr<CupHeadV> cupV2 = std::make_shared<CupHeadV>(cupM2, textures.getRedRunTextures(),
                                                                textures.getRedJumpTextures(),
                                                                textures.getRedStandingTextures());
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Cuadrado en SFML");
    bool inPlatform1 = false;
    bool inPlatform2 = false;
    sf::Clock clock, clock2;
    window.setFramerateLimit(60);





    // Función para actualizar y dibujar el primer cuphead en un thread
    auto updateAndDrawCuphead1 = [&]() {
        while (window.isOpen())
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && inPlatform1)
            {
                inPlatform1 = false;
            }
            // Verificar si el cuadrado ha llegado al piso
            if (cupM->getPosY() >= 700)
            {
                inPlatform1 = true;
            }
            float deltaTime = clock.restart().asSeconds();
            cupM->update(deltaTime,
                         sf::Keyboard::isKeyPressed(sf::Keyboard::Left),
                         sf::Keyboard::isKeyPressed(sf::Keyboard::Right),
                         sf::Keyboard::isKeyPressed(sf::Keyboard::Space),
                         inPlatform1);
            cupV->update();
        }
    };

    // Función para actualizar y dibujar el segundo cuphead en otro thread
    auto updateAndDrawCuphead2 = [&]() {
        while (window.isOpen())
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && inPlatform2)
            {
                inPlatform2 = false;
            }
            // Verificar si el cuadrado ha llegado al piso
            if (cupM2->getPosY() >= 700)
            {
                inPlatform2 = true;
            }
            float deltaTime = clock.restart().asSeconds();
            cupM2->update(deltaTime,
                          sf::Keyboard::isKeyPressed(sf::Keyboard::A),
                          sf::Keyboard::isKeyPressed(sf::Keyboard::D),
                          sf::Keyboard::isKeyPressed(sf::Keyboard::W),
                          inPlatform2);
            cupV2->update();
        }
    };

    // Iniciar los threads para los cupheads
    std::thread threadCuphead1(updateAndDrawCuphead1);
    std::thread threadCuphead2(updateAndDrawCuphead2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        cupV->draw(window);
        cupV2->draw(window);
        window.display();
    }

    // Esperar a que los threads terminen antes de salir del programa
    threadCuphead1.join();
    threadCuphead2.join();

    return 0;
}
