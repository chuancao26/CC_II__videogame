#include "Jugador_Modelo.h"
#include "Plataforma_Modelo.h"
#include "Boss_Vista.cpp"
#include "Boomerang_Controlador.cpp"
#include "Bomba_Controlador.cpp"
#include "Elegir.cpp"
#include <thread>
#include <memory>
#include "View.h"
using FloatPtr = std::shared_ptr<float>;

class Controlador {
private:
    ViewG view;
    //Modelo
    Cup jugador1;
    Cup jugador2;
    std::shared_ptr<Mapa> map;
    Plataforma pla;
    
    sf::Clock clock5, clock2;
    int nivel,j1,j2;
    vector<int> jugadores;
    bool elegidos;

    
public:
    Controlador()
    :jugador1(20,100,80), jugador2(200,100,80), view(1280, 720)
    {
        nivel = 0;
        elegidos=false;
        map = std::make_shared<Mapa>();
    }
    void crearMapa()
    {
        std::vector<std::string> mapStrings = map->crearMapa(5);
        map->parseMap(mapStrings);
    }
    void manejarEventos() {
        std::vector<FloatPtr> Posicion=std::vector<FloatPtr>();
        int m = view.procesarEventos(Posicion);
        switch (m)
        {
            case 1:
                jugador1.estaSaltando(true);
                jugador1.saltar();
                break;
            case 2:
                jugador1.vaizquierda(true);
                jugador1.moverIzquierda();
                break;
            case 3:
                jugador1.vaderecha(true);
                jugador1.moverDerecha();
                break;
            case 4:
                jugador1.moverAbajo();
                break;
            case 5:
                nivel += 1;
                break;
            case 6:
                jugador2.estaSaltando(true);
                jugador2.saltar();
                break;
            case 7:
                jugador2.vaizquierda(true);
                jugador2.moverIzquierda();
                break;
            case 8:
                jugador2.vaderecha(true);
                jugador2.moverDerecha();
                break;
            case 9:
                jugador2.moverAbajo();
                break;
            case 10:
                jugador1.vaizquierda(false);
                jugador1.vaderecha(false);
                break;
            case 11:
                jugador1.estaSaltando(false);
                break;
            case 12:
                jugador2.vaizquierda(false);
                jugador2.vaderecha(false);
                break;
            case 13:
                jugador2.estaSaltando(false);
                break;
            case 14:
                FloatPtr primerElemento = Posicion.front();
                FloatPtr segundoElemento = Posicion.back();
                sf::Vector2f mousePos(*primerElemento, *segundoElemento);
                jugadores.push_back(view.getEleccion(mousePos));
                if(jugadores.size()==2)
                    elegidos=true;
                break;
                        
        }
        jugador1.caida();
        jugador2.caida();
    }

    void Menu()
    {
        switch (nivel)
        {
        case 0:
            view.backgroundMenu(nivel);
            view.eleccionDraw();
            if(elegidos)
            {
                j1=jugadores.front();
                j2=jugadores.back();
                view.cargarJugadores(j1,j2); 
            }
            
            break;
        case 1:
            view.backgroundMenu(nivel);
            view.dibujarCup(jugador1,jugador2);
            break;
        case 2:
            view.backgroundMenu(nivel);
            crearplataformas();
            eliminarplataformas();
            view.moverPlatforms(map);
            dibujarPlataformas();
            view.dibujarCup(jugador1,jugador2);
            break;
        case 3:
            view.backgroundMenu(nivel);
            break;
        default:
            break;
        }
    }
    void eliminarplataformas()
    {
        if (clock5.getElapsedTime().asSeconds() >= 2.5f)
        {
            map->eliminarPlataformas();
            clock5.restart();
        }
    }
    void crearplataformas()
    {
        if(map->size==0)
        {
            crearMapa();
        }
        else
        {
            if (clock2.getElapsedTime().asSeconds() >= 1.0f)
            {
                map->crearPlataformas();
                clock2.restart();
                
            }
        }
        
    }
    void renderizar()
    {
        view.getWindow().setFramerateLimit(5);
        view.getWindow().clear();
        Menu();
        view.getWindow().display();
    }
    void dibujarPlataformas() {
        for(int i=0;i<map->size;i++)
        {
            view.dibujarPlat(map->platforms[i]);
        }
    }
    void colisiones() {
        for (int i=0;i<map->size;i++)
        {
            if (view.colision(view.getCup1().getSprite(), map->platforms[i]))
            {
                jugador1.enPlataforma(true);
                jugador1.estaColisionando(map->platforms[i].y);
            }
            else {
                jugador1.enPlataforma(false);
            }

            if (view.colision(view.getCup2().getSprite(), map->platforms[i]))
            {
                jugador2.enPlataforma(true);
                jugador2.estaColisionando(map->platforms[i].y);
            }
            else {
                jugador2.enPlataforma(false);
            }
        }
    }
    void ejecutar() {
        while (view.getWindow().isOpen()) {
            colisiones();
            manejarEventos();
            renderizar();
        }  
    }

};
