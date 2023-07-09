#include "Jugador_Modelo.h"
#include "Plataforma_Modelo.h"
#include "Vista.cpp"
#include "Boss_Vista.cpp"
#include "Background_Vista.cpp"
#include "Boomerang_Controlador.cpp"
#include "Bomba_Controlador.cpp"
#include <thread>

class Controlador {
private:
    Cup jugador1;
    Cup jugador2;
    Vista vista;
    Mapa map;
    Plataforma pla;
    sf::Clock clock, clock2, clock3, clock4;
    Background background;
    int nivel;

public:
    Controlador(Cup& jugador1, Cup& jugador2,int j1,int j2)
        : jugador1(jugador1), jugador2(jugador2), vista(1280, 720,j1,j2)
    {
        std::vector<std::string> mapStrings = map.crearMapa(10);
        map.parseMap(mapStrings);
        nivel = 2;
    }

    void manejarEventos() {
        // Obtener eventos de la ventana SFML
        sf::Event event;
        while (vista.window.pollEvent(event)) {
            // Manejar eventos relevantes para los jugadores
            if (event.type == sf::Event::Closed) {
                vista.window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                // Manejar teclas presionadas para el jugador 1
                if (event.key.code == sf::Keyboard::Up) {
                    jugador1.estaSaltando(true);
                    jugador1.saltar();
                }
                else if (event.key.code == sf::Keyboard::Left) {
                    jugador1.moverIzquierda();
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    jugador1.moverDerecha();
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    jugador1.moverAbajo();
                }
                else if (event.key.code == sf::Keyboard::Space) {
                    nivel += 1;
                }
                // Manejar teclas presionadas para el jugador 2
                if (event.key.code == sf::Keyboard::W) {
                    jugador2.estaSaltando(true);
                    jugador2.saltar();
                }
                else if (event.key.code == sf::Keyboard::A) {
                    jugador2.moverIzquierda();
                }
                else if (event.key.code == sf::Keyboard::D) {
                    jugador2.moverDerecha();
                }
                else if (event.key.code == sf::Keyboard::S) {
                    jugador2.moverAbajo();
                }
            }
            else if (event.type == sf::Event::KeyReleased) {
                // Manejar teclas liberadas para el jugador 1
                if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
                    //jugador1.detenerMovimientoHorizontal();
                }
                if (event.key.code == sf::Keyboard::Up) {
                    jugador1.estaSaltando(false);
                }
                // Manejar teclas liberadas para el jugador 2
                if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D) {
                    //jugador2.detenerMovimientoHorizontal();
                }
                if (event.key.code == sf::Keyboard::W) {
                    jugador2.estaSaltando(false);
                }
            }
        }
        float delta = clock3.restart().asSeconds();
        jugador1.caida(delta);
        jugador2.caida(delta);
    }

    void Menu()
    {
        switch (nivel)
        {
        case 0:
            background.cargar(vista.window, nivel);
            background.draw1(vista.window);
            break;
        case 1:
            background.cargar(vista.window, nivel);
            background.draw1(vista.window);
            vista.plataformas.clear();
            vista.dibujarCup(jugador1,1);
            vista.dibujarCup(jugador2,2);
            dibujarPlataformas();
            break;
        case 2:
            background.cargar(vista.window, nivel);
            background.draw2(vista.window);
            map.eliminarPlataformas();
            crearplataformas();
            vista.plataformas.clear();
            mover_plataformas();
            vista.dibujarCup(jugador1,1);
            vista.dibujarCup(jugador2,2);
            dibujarPlataformas();
            break;
        case 3:
            background.cargar(vista.window, nivel);
            background.draw1(vista.window);
            break;
        default:
            break;
        }
    }
    void crearplataformas()
    {
        if (clock2.getElapsedTime().asSeconds() >= 2.5f)
        {
            map.crearPlataformas();
            clock2.restart();
        }
    }
    void renderizar() {
        vista.window.clear();
        Menu();
        vista.window.display();
    }
    void dibujarPlataformas() {
        for (auto& platform : map.platforms)
        {
            vista.dibujarPlat(platform);
        }
    }
    void colisiones() {
        for (auto platform : vista.plataformas)
        {
            if (vista.colision(vista.jugador_v.cupShape, platform))
            {
                jugador1.enPlataforma(true);
                jugador1.estaColisionando(platform->pla.getPosy());
            }
            else {
                jugador1.enPlataforma(false);
            }

            if (vista.colision(vista.jugador_v2.cupShape, platform))
            {
                jugador2.enPlataforma(true);
                jugador2.estaColisionando(platform->pla.getPosy());
            }
            else {
                jugador2.enPlataforma(false);
            }
        }
    }
    void mover_plataformas() {
        float delta = clock.restart().asSeconds();
        for (auto& platform : map.platforms) {
            platform.caida(delta);
            dibujarPlataformas();
        }
        background.actualizar(vista.window, delta);
    }

    void ejecutar() {
        std::thread hiloJugador2([this] {
            while (vista.window.isOpen()) {
                manejarEventos();
            }
        });

        while (vista.window.isOpen()) {
            colisiones();
            manejarEventos();
            renderizar();
        }

        hiloJugador2.join();
    }
};
