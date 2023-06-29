#include "Jugador_Modelo.h"
#include "Plataforma_Modelo.h"
#include "Vista.cpp"

class Controlador {
private:
    Cup jugador;
    Vista vista;
    Mapa map;
    Plataforma pla;
    sf::Clock clock;

public:
    Controlador(Cup& jugador,std::vector<std::string> mapStrings)
        : jugador(jugador),vista(1280,720)
    {
        map = Mapa::parseMap(mapStrings);
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
                
                //jugador.caida();
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
    void actualizar() {
        
    }

    void renderizar() {
        vista.window.clear();
        vista.plataformas.clear();
        vista.dibujarCup(jugador);
        dibujarPlataformas();
        vista.window.display();
    }
    void dibujarPlataformas(){
        for (const auto& platform : map.platforms)
        {
            vista.dibujarPlat(platform);
        }
    }
    void colisiones(){
        for (const auto& platform : vista.plataformas)
        {
            if (vista.colision(vista.jugador_v.cupShape,platform))
            {
                jugador.enPlataforma(true);
                jugador.estaColisionando(platform.pla.getPosy());
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
