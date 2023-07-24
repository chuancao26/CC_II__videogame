#ifndef VIEW_H
#define VIEW_H
#include <SFML/Graphics.hpp>
#include "Jugador_Vista.cpp"
#include "Plataforma_Vista.cpp"
#include "vistaBee.h"
#include "Background_Vista.cpp"
#include <memory>
#include "Elegir.cpp"
using FloatPtr = std::shared_ptr<float>;
class ViewG
{
private:
    sf::RenderWindow window;
    JugadorVista jugador_v;
    JugadorVista jugador_v2;
    float width, height, deltaTimePlat, timeElapsed;
    sf::Clock clock, clock2;
    VistaBee vistaBee;
    Background background;
    ElegirPlayer elegir;
public:
    ViewG(const int& xedge, const int& yedge):
    width(xedge), height(yedge), window(sf::VideoMode(xedge, yedge), "CUPHEAD!"),
    vistaBee(window)
    {
        jugador_v.cargar(1);
    }
    void dibujarCup(const Cup& jugador1/*,const Cup& jugador2*/)
    {
        jugador_v.dibujar(jugador1,window);
        // jugador_v2.dibujar(jugador2,window);
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
    bool ventanaAbierta()
    {
        return window.isOpen();
    }
    void 

    // int procesarEventos(std::vector<FloatPtr>& Posicion) {
    //     sf::Event event;
    //     if (window.pollEvent(event)) {
    //         if (event.type == sf::Event::Closed) {
    //             window.close();
    //         }
            
    //         else if (event.type == sf::Event::KeyPressed) {
    //             // Manejar teclas presionadas para el jugador 1
    //             if (event.key.code == sf::Keyboard::Up) {
    //                 //Acciones.push_back(std::make_shared<std::string>("Up"));
    //                 return 1;
    //             }
    //             else if (event.key.code == sf::Keyboard::Left) {
    //                 return 2;
    //             }
    //             else if (event.key.code == sf::Keyboard::Right) {
    //                 return 3;
    //             }
    //             else if (event.key.code == sf::Keyboard::Down) {
    //                 return 4;
    //             }
    //             else if (event.key.code == sf::Keyboard::Space) {
    //                 return 5;
    //             }
    //             // Manejar teclas presionadas para el jugador 2
    //             if (event.key.code == sf::Keyboard::W) {
    //                 return 6;
    //             }
    //             else if (event.key.code == sf::Keyboard::A) {
    //                 return 7;
    //             }
    //             else if (event.key.code == sf::Keyboard::D) {
    //                 return 8;
    //             }
    //             else if (event.key.code == sf::Keyboard::S) {
    //                 return 9;
    //             }
    //         }
    //         else if (event.type == sf::Event::KeyReleased) {
    //             // Manejar teclas liberadas para el jugador 1
    //             if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
    //                 return 10;
    //             }
    //             if (event.key.code == sf::Keyboard::Up) {
    //                 return 11;
    //             }
    //             // Manejar teclas liberadas para el jugador 2
    //             if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D) {
    //                 return 12;
    //             }
    //             if (event.key.code == sf::Keyboard::W) {
    //                 return 13;
    //             }
    //         }
    //         else if (event.type == sf::Event::MouseButtonPressed) {
    //             if (event.mouseButton.button == sf::Mouse::Left) {
    //                 sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    //                 sf::Vector2f mousePos(mousePosition.x, mousePosition.y);
    //                 Posicion.push_back(std::make_shared<float>(mousePosition.x));
    //                 Posicion.push_back(std::make_shared<float>(mousePosition.y));
    //                 return 14;
    //             }
    //         }
    //     }
    //     return 0;
    // }
    void loadBeeView(const Cup& player1, const Cup& player2)
    {
        vistaBee.handleInput(player1, player2);
        vistaBee.render();
    }
    void backgroundMenu(const int& n)
    {
        background.cargar(window, n);
        if (n == 0 || n == 1 || n == 3)
            background.draw1(window);
        else
            background.draw2(window);
    }
    int getEleccion(const sf::Vector2f& mousePos)
    {
        return elegir.seleccionar(mousePos);
    }
    void eleccionDraw()
    {
        elegir.dibujar(window);
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
    sf::RenderWindow& getWindow()
    {
        return window;
    }
    JugadorVista& getCup1()
    {
        return jugador_v;
    }
    JugadorVista& getCup2()
    {
        return jugador_v2;
    }
    float getElapsedTime()
    {
        return clock2.getElapsedTime().asSeconds();
    }
    
};
#endif