#include <SFML/Graphics.hpp>
#include "Jugador_Vista.cpp"
#include "Plataforma_Vista.cpp"
#include "Background_Vista.cpp"
#include "Elegir.cpp"
#include "eventosflor.h"
#include <thread>
#include <memory>
#include "vistaBee.h"
#include <iostream>
using FloatPtr = std::shared_ptr<float>;
class Vista {
public:
    sf::RenderWindow window;
    JugadorVista jugador_v;
    JugadorVista jugador_v2;
    float width,height;
    VistaBee vistaBee;
    VistaFlor vistaFlor;
    ElegirPlayer elegir;
    Background background;
    sf::Clock clock, gameTime, clock5;

    
public:
    Vista(const int& xedge, const int& yedge) : width(xedge), height(yedge), window(sf::VideoMode(xedge, yedge), "CUPHEAD!")
    , vistaBee(window), vistaFlor(window)
    {
        width = window.getSize().x;
        height = window.getSize().y;  
    }
    void cargarJugadores(int j1,int j2)
    {
        if(j1!=0 && j2!=0)
        {
            jugador_v.cargar(j1);
            jugador_v2.cargar(j2); 
        }
        
    }
    float getGameTime()
    {
        return gameTime.getElapsedTime().asSeconds();
    }
    void dibujarCup(const Cup& jugador1,const Cup& jugador2) {
        jugador_v.dibujar(jugador1,window);
        jugador_v2.dibujar(jugador2,window);
    }

    void dibujarPlat(const Plataforma& plataforma) {
       
        PlataformaVista plat(plataforma);
        plat.setPosition(plataforma.getPosx(), plataforma.getPosy());
        window.draw(plat.get());
    }
    void loadBeeView(const Cup& player1, const Cup& player2 )
    {
        vistaBee.handleInput(player1,player2, getGameTime());
        vistaBee.render();
    }
    void loadFlorView(const Cup& player1, const Cup& player2, sf::RenderWindow& win)
    {
        vistaFlor.handleInput(player1,player2,win);
        vistaFlor.render(win);
    }
    
    bool colision(sf::Sprite& jugador, Plataforma& platform)
    {
        sf::FloatRect jugadorBounds = jugador.getGlobalBounds();
        sf::FloatRect plataformaBounds(platform.x, platform.y, platform.width,platform.height);
        return jugadorBounds.intersects(plataformaBounds);
    }

    bool ventanaAbierta() {
        return window.isOpen();
    }

    int procesarEventos(std::vector<FloatPtr>& Posicion) {
        sf::Event event;
        if (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            else if (event.type == sf::Event::KeyPressed) {
                // Manejar teclas presionadas para el jugador 1
                if (event.key.code == sf::Keyboard::Up) {
                    //Acciones.push_back(std::make_shared<std::string>("Up"));
                    return 1;
                }
                else if (event.key.code == sf::Keyboard::Left) {
                    return 2;
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    return 3;
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    return 4;
                }
                else if (event.key.code == sf::Keyboard::Space) {
                    return 5;
                }
                // Manejar teclas presionadas para el jugador 2
                if (event.key.code == sf::Keyboard::W) {
                    return 6;
                }
                else if (event.key.code == sf::Keyboard::A) {
                    return 7;
                }
                else if (event.key.code == sf::Keyboard::D) {
                    return 8;
                }
                else if (event.key.code == sf::Keyboard::S) {
                    return 9;
                }
            }
            else if (event.type == sf::Event::KeyReleased) {
                // Manejar teclas liberadas para el jugador 1
                if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
                    return 10;
                }
                if (event.key.code == sf::Keyboard::Up) {
                    return 11;
                }
                // Manejar teclas liberadas para el jugador 2
                if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D) {
                    return 12;
                }
                if (event.key.code == sf::Keyboard::W) {
                    return 13;
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    sf::Vector2f mousePos(mousePosition.x, mousePosition.y);
                    Posicion.push_back(std::make_shared<float>(mousePosition.x));
                    Posicion.push_back(std::make_shared<float>(mousePosition.y));
                    return 14;
                }
            }
        }
        return 0;
    }
    sf::RenderWindow& getWindow()
    {
        return window;
    }
    void eliminarplataformas(Mapa*& map)
    {
        if (clock5.getElapsedTime().asSeconds() >= 2.5f)
        {
            map->eliminarPlataformas();
            clock5.restart();
        }
    }
};

