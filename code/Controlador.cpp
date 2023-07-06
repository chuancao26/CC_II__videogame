#include "Jugador_Modelo.h"
#include "Plataforma_Modelo.h"
#include "Vista.cpp"
#include "Boss_Vista.cpp"
#include "Background_Vista.cpp"
#include "Boomerang_Controlador.cpp"
#include "Bomba_Controlador.cpp"

class Controlador {
private:
    Cup jugador;
    Vista vista;
    Mapa map;
    Plataforma pla;
    sf::Clock clock;
    Background background;
    int nivel;

public:
    Controlador(Cup& jugador,std::vector<std::string> mapStrings)
        : jugador(jugador),vista(1280,720)
    {
        map = Mapa::parseMap(mapStrings);
        nivel=2;
    }

    void manejarEventos() {
        // Obtener eventos de la ventana SFML
        sf::Event event;
        while (vista.window.pollEvent(event)) {
            // Manejar eventos relevantes para el jugador
            if (event.type == sf::Event::Closed) {
                vista.window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                // Manejar teclas presionadas
                if (event.key.code == sf::Keyboard::Up) {
                    jugador.estaSaltando(true);
                    jugador.saltar();
                }
                else if (event.key.code == sf::Keyboard::Left) {
                    jugador.moverIzquierda();
                    //jugador.mover(jugador.getPosx()-1.0f,jugador.getPosy());
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    jugador.moverDerecha();
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    jugador.moverAbajo();
                }
                else if (event.key.code == sf::Keyboard::Space) {
                    nivel+=1;
                }
            }
            else if (event.type == sf::Event::KeyReleased) {
                // Manejar teclas liberadas
                if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
                    //jugador.detenerMovimientoHorizontal();
                }
                if (event.key.code == sf::Keyboard::Up) {
                    jugador.estaSaltando(false);
                }
            }
        }
        jugador.caida();
    }

    void Menu()
    {
        switch (nivel)
        {
            case 0:
                background.cargar(vista.window,nivel);
                background.draw(vista.window);
                break;
            case 1:
                background.cargar(vista.window,nivel);
                background.draw(vista.window);
                vista.plataformas.clear();
                vista.dibujarCup(jugador);
                dibujarPlataformas();
                break;
            case 2:
                background.cargar(vista.window,nivel);
                background.draw(vista.window);
                vista.plataformas.clear();
                vista.dibujarCup(jugador);
                dibujarPlataformas();
                break;
            case 3:
                background.cargar(vista.window,nivel);
                background.draw(vista.window);
                break;
            default:
                break;
        }
    }

    void renderizar() {
        vista.window.clear();
        Menu();
        vista.window.display();
    }
    void dibujarPlataformas(){
        for ( auto& platform : map.platforms)
        {
            if(platform.getPosy()>500)
            {
                float nposy=map.platforms.back().getPosy()-50;
                platform.setPosition(platform.getPosx(),nposy);
                
            }
            vista.dibujarPlat(platform);
        }
    }
    void colisiones(){
        for (auto platform : vista.plataformas)
        {
            if (vista.colision(vista.jugador_v.cupShape,platform))
            {
                jugador.enPlataforma(true);
                jugador.estaColisionando(platform->pla.getPosy());
            }
            jugador.enPlataforma(false);
        }
    }
    void mover_plataformas() {
        if (clock.getElapsedTime().asSeconds() >= 1.0f) 
        {
            for (auto& platform : map.platforms) {
                platform.caida();
                dibujarPlataformas();
            }

        clock.restart();
        }
    }
    
    void ejecutar() {
        while (vista.window.isOpen()) {
            mover_plataformas();
            colisiones();
            manejarEventos();
            renderizar();
        }
    }
};