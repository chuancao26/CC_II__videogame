#include "Jugador_Modelo.h"
#include "Plataforma_Modelo.h"
#include "Jugador_Vista.cpp"

class JugadorControlador {
private:
    Cup& jugador;
    JugadorVista& vista;
    Mapa map;
    Plataforma pla;
    bool collision = false;
    bool onPlatform = false;

public:
    JugadorControlador(Cup& jugador, JugadorVista& vista,std::vector<std::string> mapStrings)
        : jugador(jugador), vista(vista) 
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
        vista.dibujar(jugador);
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
            if (vista.colision(vista.cupShape,platform))
            {
                jugador.enPlataforma(true);
                jugador.estaColisionando(platform.pla.getPosy());
            }
            jugador.enPlataforma(false);
        }
    }

    void ejecutar() {
        while (vista.window.isOpen()) {
            vista.actualizar(jugador);
            colisiones();
            manejarEventos();
            renderizar();
        }
    }
};
