
#ifndef BOMBCONTROLLER_H
#define BOMBCONTROLLER_H
#include "bombview.h"
#include "bombmodel.h"
#include <iostream>


class BombController {
private:
    std::vector<BombModel> bombs;
    BombView cuadradoView;
    bool Eliminar;
public:
    BombController(float ventanaAncho, float ventanaAlto) : bombs(1), cuadradoView(){
        for (int i = 0; i < 1; i++) {
                float posicionX = static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX) / (ventanaAncho * 3 / 5));
                bombs[i] = BombModel(ventanaAncho, ventanaAlto);
                bombs[i].setX(posicionX);
                bombs[i].caer();
        }
    }

    void update() {
        for (auto& bomb : bombs) {
            bomb.caer();
        }
    }


    void draw(sf::RenderWindow& window) {
        for (const auto& cuadrado : bombs) {
            if (!cuadrado.isEliminado()) {
                cuadradoView.setSize(cuadrado.getSize());
                cuadradoView.setPosition(cuadrado.getX(), cuadrado.getY());

                if (cuadrado.llegoMaximo) {
                    cuadradoView.setTexturePiso();
                } else {
                    cuadradoView.setTextureCae();
                }

                cuadradoView.draw(window);
                bool Eliminar=false;
            }
            else if (!cuadrado.isEliminado()){
                Eliminar=true;
            }
        }
    }
    
    bool Eliminado(){

        return Eliminar;
    }
    

};
#endif