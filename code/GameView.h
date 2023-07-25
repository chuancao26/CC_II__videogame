#ifndef GAMEVIEW_H
#define GAMEVIEW_H
#include <SFML/Graphics.hpp>
#include <memory>
#include "Background_Vista.h"
#include <iostream>
#include "Textures.h"
#include "Cup.h"
#include "Plataforma_Vista.h"
class GameView
{
private:
    Textures textures;
    std::shared_ptr<CupHeadM> cupM;
    std::shared_ptr<CupHeadV> cupV;
    float width, height, deltaTimePlat, timeElapsed;
    sf::Clock clock, clock2;
    sf::RectangleShape rect;
    Background background;
    bool isRight, isLeft, isUp;
public:
    sf::RenderWindow window;
    GameView():window(sf::VideoMode(1280,720), "Prueba")
    {
        rect.setFillColor(sf::Color::Red);
        rect.setSize(sf::Vector2f(50,50));
        rect.setPosition(400,200);
    }
    void render()
    {
        window.clear();
        window.draw(rect);
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
        updateTeclas();
    }
    bool isOpen()
    {
        return window.isOpen();
    }
    void dibujarPlat(const std::shared_ptr<Mapa>& map)
    {
        for(int i=0;i<map->size;i++)
        {
            PlataformaVista plat(map->platforms[i]);
            plat.setPosition(map->platforms[i].getPosx(), map->platforms[i].getPosy());
            window.draw(plat.get());
        } 
    }
    bool colision(sf::Sprite& jugador, Plataforma& platform)
    {
        sf::FloatRect jugadorBounds = jugador.getGlobalBounds();
        sf::FloatRect plataformaBounds(platform.x, platform.y, platform.width,platform.height);
        return jugadorBounds.intersects(plataformaBounds);
    }
    void updateTeclas()
    {
        isRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
        isUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        isLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    }
    bool getIsLeft()
    {
        return isLeft;
    }
    bool getIsRight(){return isRight;}
    bool getIsUp(){return isUp;}
    void backgroundMenu(const int& n)
    {
        background.cargar(window, n);
        if (n == 0 || n == 1 || n == 3)
            background.draw1(window);
        else
            background.draw2(window);
    }
    void moverPlatforms(const std::shared_ptr<Mapa>& map)
    {
        deltaTimePlat = clock.restart().asSeconds();
        for(int i=0;i<map->size;i++)
        {
            map->platforms[i].caida(deltaTimePlat);
        }
        background.actualizar(window,deltaTimePlat);
    }
    float getElapsedTime()
    {
        return clock2.getElapsedTime().asSeconds();
    }
};

#endif