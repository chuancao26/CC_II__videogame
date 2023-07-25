#ifndef GAMEVIEW_H
#define GAMEVIEW_H
#include <SFML/Graphics.hpp>
#include <memory>
#include "Background_Vista.h"
#include <iostream>
#include "Plataforma_Vista.h"
class GameView
{
private:
    sf::RenderWindow window;
    float width, height, deltaTimePlat, timeElapsed;
    sf::Clock clock, clock2;
    sf::RectangleShape rect;
    Background background;
    bool isRight, isLeft, isUp;
public:
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
};
#endif