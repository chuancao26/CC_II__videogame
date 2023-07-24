#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Jugador_Modelo.h"
#include "Plataforma_Modelo.h"
#include "Boss_Vista.cpp"
#include "Boomerang_Controlador.cpp"
#include "Bomba_Controlador.cpp"
#include "Elegir.cpp"
#include <thread>
#include <memory>
#include "View.h"
#include "Model.h"
class Controller
{
private:
    ViewG view;
    Model model;
    
    //teclas
    bool isUp, isLeft, isright, isSpace;
    float elapsedTime;
    int xEdge, yEdge;
    std::shared_ptr<Mapa> map;
    Plataforma pla;
public:
    Controller():xEdge(1280), yEdge(720), view(xEdge, yEdge), elapsedTime(view.getElapsedTime())
    {
        view.getWindow().setFramerateLimit(60);
    }
    void render()
    {
        view.getWindow().clear();

        view.getWindow().display();
    }
    void manejarTeclas()
    {

    }
    void nivelBee()
    {
        //Background nivel bee = 2
        view.backgroundMenu(2);
        model.crearPlataformas();
        model.eliminarPlataformas();
        view.moverPlatforms(model.getMap());
        view.dibujarPlat(model.getMap());
        view.dibujarCup(model.getPlayer1());
    }
    void update()
    {
        elapsedTime = view.getElapsedTime();
        model.update(elapsedTime);
    }
    void ejecutar()
    {
        while(view.getWindow().isOpen())
        {
            update();
            render();
        }
    }



};
#endif