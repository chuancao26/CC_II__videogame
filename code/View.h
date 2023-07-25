#ifndef VIEW_H
#define VIEW_H
#include <SFML/Graphics.hpp>
#include "Plataforma_Vista.h"
#include "Background_Vista.h"
#include <memory>
#include <iostream>
class ViewG
{
private:
    sf::RenderWindow window;
    // JugadorVista jugador_v;
    // JugadorVista jugador_v2;
    sf::RectangleShape cuad;
    float width, height, deltaTimePlat, timeElapsed;
    sf::Clock clock, clock2;
    // VistaBee vistaBee;
    Background background;
    bool isRight, isLeft, isUp;
public:
    ViewG():
    width(1280), height(720), window(sf::VideoMode(width, height), "CUPHEAD!")
    // vistaBee(window)
    {
        cuad.setFillColor(sf::Color::Red);
        cuad.setSize(sf::Vector2f(50,50));
        cuad.setPosition(width / 2, height / 2);
        // jugador_v.cargar(1);
    }
    void render() // const std::shared_ptr<Mapa>& map
    {
        window.clear();
        std::cout << "dibujando" << std::endl;
        window.draw(cuad);
        // moverPlatforms(map);
        // dibujarPlat(map);
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
    // void dibujarCup(const Cup& jugador1/*,const Cup& jugador2*/)
    // {
    //     jugador_v.dibujar(jugador1,window);
    //     // jugador_v2.dibujar(jugador2,window);
    // }
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
    bool isOpen()
    {
        return window.isOpen();
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
    void update()
    {
        updateTeclas();
    }
    void backgroundMenu(const int& n)
    {
        background.cargar(window, n);
        if (n == 0 || n == 1 || n == 3)
            background.draw1(window);
        else
            background.draw2(window);
    }
    // int getEleccion(const sf::Vector2f& mousePos)
    // {
    //     return elegir.seleccionar(mousePos);
    // }
    // void eleccionDraw()
    // {
    //     elegir.dibujar(window);
    // }
    void moverPlatforms(const std::shared_ptr<Mapa>& map)
    {
        deltaTimePlat = clock.restart().asSeconds();
        for(int i=0;i<map->size;i++)
        {
            map->platforms[i].caida(deltaTimePlat);
        }
        background.actualizar(window,deltaTimePlat);
    }
    sf::RenderWindow& getWindow()
    {
        return window;
    }
    // JugadorVista getCup1()
    // {
    //     return jugador_v;
    // }
    // JugadorVista getCup2()
    // {
    //     return jugador_v2;
    // }
    float getElapsedTime()
    {
        return clock2.getElapsedTime().asSeconds();
    }



    
};
#endif