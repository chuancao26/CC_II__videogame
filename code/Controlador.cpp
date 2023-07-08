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
    sf::Clock clock,clock2;
    Background background;
    int nivel;

public:
    Controlador(Cup& jugador,std::vector<std::string> mapStrings)
        : jugador(jugador),vista(1280,720)
    {   
        //std::vector<std::string> mapStrings=map.crearMapa(8);
        map.parseMap(mapStrings);
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
                background.draw1(vista.window);
                break;
            case 1:
                background.cargar(vista.window,nivel);
                background.draw1(vista.window);
                vista.plataformas.clear();
                vista.dibujarCup(jugador);
                dibujarPlataformas();
                break;
            case 2:
                background.cargar(vista.window,nivel);
                background.draw2(vista.window);
                vista.plataformas.clear();
                map.eliminarPlataformas();
                crearplataformas();
                mover_plataformas();
                vista.dibujarCup(jugador);
                dibujarPlataformas();
                break;
            case 3:
                background.cargar(vista.window,nivel);
                background.draw1(vista.window);
                break;
            default:
                break;
        }
    }
    void crearplataformas()
    {
        if (clock2.getElapsedTime().asSeconds() >= 8.0f) 
        {
            vector<string> m=map.crearMapa(1);
            map.parseMap(m);
            clock2.restart();
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
        if (clock.getElapsedTime().asSeconds() >= 0.5f) 
        {
            for (auto& platform : map.platforms) {
                platform.caida();
                dibujarPlataformas();
            }
            background.actualizar(vista.window);

        clock.restart();
        }
    }
    
    void ejecutar() {
        while (vista.window.isOpen()) {
            colisiones();
            manejarEventos();
            renderizar();
        }
    }
};