#include "Jugador_Modelo.h"
#include "Plataforma_Modelo.h"
#include "Vista.cpp"
#include "Boss_Vista.cpp"
#include "Background_Vista.cpp"
#include "Boomerang_Controlador.cpp"
#include "Bomba_Controlador.cpp"
#include "Elegir.cpp"
#include <thread>

class Controlador {
private:
    Cup jugador1;
    Cup jugador2;
    Vista vista;
    Mapa map;
    ElegirPlayer elegir;
    Plataforma pla;
    sf::Clock clock, clock2, clock3, clock4,clock5;
    Background background;
    int nivel,j1,j2;
    vector<int> jugadores;
    bool elegidos;

public:
    Controlador()
        : jugador1(20,100,80), jugador2(200,100,80), vista(1280, 720)
    {
        std::vector<std::string> mapStrings = map.crearMapa(10);
        map.parseMap(mapStrings);
        nivel = 0;j1=0;j2=0;
        elegidos=false;
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
                    jugador1.vaizquierda(true);
                    jugador1.moverIzquierda();
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    jugador1.vaderecha(true);
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
                    jugador2.vaizquierda(true);
                    jugador2.moverIzquierda();
                }
                else if (event.key.code == sf::Keyboard::D) {
                    jugador2.vaderecha(true);
                    jugador2.moverDerecha();
                }
                else if (event.key.code == sf::Keyboard::S) {
                    jugador2.moverAbajo();
                }
            }
            else if (event.type == sf::Event::KeyReleased) {
                // Manejar teclas liberadas para el jugador 1
                if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
                    jugador1.vaizquierda(false);
                    jugador1.vaderecha(false);
                }
                if (event.key.code == sf::Keyboard::Up) {
                    jugador1.estaSaltando(false);
                }
                // Manejar teclas liberadas para el jugador 2
                if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D) {
                    jugador2.vaizquierda(false);
                    jugador2.vaderecha(false);
                }
                if (event.key.code == sf::Keyboard::W) {
                    jugador2.estaSaltando(false);
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(vista.window);
                    sf::Vector2f mousePos(mousePosition.x, mousePosition.y);
                    jugadores.push_back(elegir.seleccionar(mousePos,true));
                    if(jugadores.size()==2)
                        elegidos=true;
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    // Código para el clic derecho del mouse
                    std::cout << "Clic derecho del mouse" << std::endl;
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
            elegir.dibujar(vista.window);
            if(elegidos)
            {
                j1=jugadores.front();
                j2=jugadores.back();
                vista.cargarJugadores(j1,j2); 
            }
            
            break;
        case 1:
            
            background.cargar(vista.window, nivel);
            background.draw1(vista.window);
            
            vista.plataformas.clear();
            vista.dibujarCup(jugador1,jugador2);
            break;
        case 2:
            background.cargar(vista.window, nivel);
            background.draw2(vista.window);
            eliminarplataformas();
            cout<<map.platforms.size()<<endl;
            crearplataformas();
            vista.plataformas.clear();
            mover_plataformas();
            dibujarPlataformas();
            vista.dibujarCup(jugador1,jugador2);
            break;
        case 3:
            background.cargar(vista.window, nivel);
            background.draw1(vista.window);
            break;
        default:
            break;
        }
    }
    void eliminarplataformas()
    {
        if (clock5.getElapsedTime().asSeconds() >= 1.0f)
        {
            map.eliminarPlataformas();
            clock5.restart();
        }
    }
    void crearplataformas()
    {
        if (clock2.getElapsedTime().asSeconds() >= 2.75f)
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
        }
        background.actualizar(vista.window, delta);
    }

    void ejecutar() {
        if(nivel>0)
        {
            std::thread hiloJugador2([this] {
                while (vista.window.isOpen()) {
                    manejarEventos();
                }
            }); 
            
            hiloJugador2.join();
        }

        while (vista.window.isOpen()) {
            colisiones();
            manejarEventos();
            renderizar();
        }  
    }
};
