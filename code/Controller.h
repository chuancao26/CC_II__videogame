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
    Model model;
    GameView view;
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
        model.crearPlataformas();
        model.eliminarPlataformas();
        // view.dibujarCup(model.getPlayer1());
    }
    void update()
    {
        elapsedTime = view.getElapsedTime();
        model.update(elapsedTime);

    }
    void run()
    {
        while(view.isOpen())
        {
            view.handleInput(model.getMap());
            view.render();
        }
    }



};

#endif