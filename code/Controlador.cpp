#include "Modelo.cpp"
#include "Vista.cpp"
#include "Boss_Vista.cpp"
#include "Background_Vista.cpp"
#include "Boomerang_Controlador.cpp"
#include "Bomba_Controlador.cpp"
#include "Elegir.cpp"
#include <thread>
#include <memory>
#include "vistaBee.h"
using FloatPtr = std::shared_ptr<float>;

class Controlador {
private:
    //Modelo
    Modelo modelo;

    //Vista
    Vista vista;
    VistaBee vistaBee;
    ElegirPlayer elegir;
    Background background;
    sf::Clock clock, clock2,clock5;
    bool elegidos;
    
    //float clock,clock2,clock3;
    int nivel,j1,j2;
    vector<int> jugadores;

public:
    Controlador()
        : vista(1280, 720), vistaBee(vista.getWindow())
    {
        nivel = 0;
        elegidos=false;
    }
    void crearMapa()
    {
        std::vector<std::string> mapStrings = modelo.map->crearMapa(50);
        modelo.map->parseMap(mapStrings);
    }
    void manejarEventos() {
        std::vector<FloatPtr> Posicion=std::vector<FloatPtr>();
        int m=vista.procesarEventos(Posicion);
        switch (m)
        {
            case 1:
                modelo.jugador1.estaSaltando(true);
                modelo.jugador1.saltar();
                break;
            case 2:
                modelo.jugador1.vaizquierda(true);
                modelo.jugador1.moverIzquierda();
                break;
            case 3:
                modelo.jugador1.vaderecha(true);
                modelo.jugador1.moverDerecha();
                break;
            case 4:
                modelo.jugador1.moverAbajo();
                break;
            case 5:
                nivel += 1;
                break;
            case 6:
                modelo.jugador2.estaSaltando(true);
                modelo.jugador2.saltar();
                break;
            case 7:
                modelo.jugador2.vaizquierda(true);
                modelo.jugador2.moverIzquierda();
                break;
            case 8:
                modelo.jugador2.vaderecha(true);
                modelo.jugador2.moverDerecha();
                break;
            case 9:
                modelo.jugador2.moverAbajo();
                break;
            case 10:
                modelo.jugador1.vaizquierda(false);
                modelo.jugador1.vaderecha(false);
                break;
            case 11:
                modelo.jugador1.estaSaltando(false);
                break;
            case 12:
                modelo.jugador2.vaizquierda(false);
                modelo.jugador2.vaderecha(false);
                break;
            case 13:
                modelo.jugador2.estaSaltando(false);
                break;
            case 14:
                FloatPtr primerElemento = Posicion.front();
                FloatPtr segundoElemento = Posicion.back();
                sf::Vector2f mousePos(*primerElemento, *segundoElemento);
                jugadores.push_back(elegir.seleccionar(mousePos,true));
                if(jugadores.size()==2)
                    elegidos=true;
                break;
                        
        }
        modelo.jugador1.caida();
        modelo.jugador2.caida();
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
            background.draw2(vista.window);
            crearplataformas();
            eliminarplataformas();
            mover_plataformas();
            dibujarPlataformas();
            vista.dibujarCup(modelo.jugador1,modelo.jugador2);
            loadBeeView();
            break;
        case 2:
            
            background.cargar(vista.window, nivel);
            background.draw1(vista.window);
            vista.dibujarCup(modelo.jugador1,modelo.jugador2);
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
        if (clock5.getElapsedTime().asSeconds() >= 2.5f)
        {
            modelo.map->eliminarPlataformas();
            clock5.restart();
        }
    }
    void crearplataformas()
    {
        if(modelo.map->size==0)
        {
            crearMapa();
        }
        /*else
        {
            if (clock2.getElapsedTime().asSeconds() >= 1.0f)
            {
                map->crearPlataformas();
                clock2.restart();
                
            }
        }*/
        
    }
    void renderizar() {
        vista.window.clear();
        Menu();
        vista.window.display();
    }
    void dibujarPlataformas() {
        for(int i=0;i<modelo.map->size;i++)
        {
            vista.dibujarPlat(modelo.map->platforms[i]);
        }
    }
    void colisiones() {
        for (int i=0;i<modelo.map->size;i++)
        {
            if (vista.colision(vista.jugador_v.cupShape, modelo.map->platforms[i]))
            {
                modelo.jugador1.enPlataforma(true);
                modelo.jugador1.estaColisionando(modelo.map->platforms[i].y);
            }
            else {
                modelo.jugador1.enPlataforma(false);
            }

            if (vista.colision(vista.jugador_v2.cupShape, modelo.map->platforms[i]))
            {
                modelo.jugador2.enPlataforma(true);
                modelo.jugador2.estaColisionando(modelo.map->platforms[i].y);
            }
            else {
                modelo.jugador2.enPlataforma(false);
            }
        }
    }
    void mover_plataformas() {
        float delta = clock.restart().asSeconds();
        for(int i=0;i<modelo.map->size;i++)
        {
            modelo.map->platforms[i].caida(delta);
        }
        background.actualizar(vista.window, delta);
    }
    void ejecutar() {


        while (vista.window.isOpen()) {
            colisiones();
            manejarEventos();
            renderizar();
        }  
    }
    void loadBeeView()
    {
        vistaBee.handleInput(modelo.jugador1,modelo.jugador2);
        vistaBee.render();
    }
};
