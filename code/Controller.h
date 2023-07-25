#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <thread>
#include <memory>
#include <iostream>
#include "View.h"
#include "Model.h"
#include "GameView.h"
class Controller
{
private:
    ViewG view;
    Model model;
    GameView view2;
    //teclas
    float elapsedTime;
    std::shared_ptr<Mapa> map;
    Plataforma pla;
public:
    Controller() // elapsedTime(view.getElapsedTime())
    {
    }
    // void render()
    // {
    //     view.getWindow().clear();
    //     // nivelBee();
    //     view.getWindow().display();
    // }
    void nivelBee()
    {
        //Background nivel bee = 2
        view.backgroundMenu(2);
        model.crearPlataformas();
        model.eliminarPlataformas();
        view.moverPlatforms(model.getMap());
        view.dibujarPlat(model.getMap());
        // view.dibujarCup(model.getPlayer1());
    }
    void update()
    {
        elapsedTime = view.getElapsedTime();
        model.update(elapsedTime);
        view.update();

    }
    void run()
    {
        while(view2.isOpen())
        {
            view2.handleInput();
            // update();
            view2.render();
            
        }
    }



};

#endif