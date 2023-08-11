
#ifndef BOMBCONTROLLER_H
#define BOMBCONTROLLER_H
#include "bombview.h"
#include "bombmodel.h"
#include <iostream>


class BombController {
private:
    BombModel bombs;
    BombView cuadradoView;
    bool Eliminar;
public:
    BombController(float ventanaAncho, float ventanaAlto) : bombs(),cuadradoView(),Eliminar(false){
        float posicionX = static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX) / (ventanaAncho * 3 / 5));
        bombs = BombModel(ventanaAncho, ventanaAlto);
        bombs.setX(posicionX);
        bombs.caer();

    }

    void update() { 

        bombs.caer();

    }


    void draw(sf::RenderWindow& window) {

            if (!bombs.isEliminado()) {
                cuadradoView.setSize(bombs.getSize());
                cuadradoView.setPosition(bombs.getX(), bombs.getY());

                if (bombs.llegoMaximo) {
                    cuadradoView.setTexturePiso();
                } else {
                    cuadradoView.setTextureCae();
                }

                cuadradoView.draw(window);
                //Eliminar=false;
                bombs.Eliminado(false);
            }
            else {
                bombs.Eliminado(true);
            }
        
    }
    
    bool Eliminado(){

        return bombs.isEliminado();
    }
    sf::Sprite& getSprite()
    {
        return cuadradoView.getSprite(); 
    }

};
#endif