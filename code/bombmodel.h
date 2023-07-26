#ifndef BOMBMODEL_H
#define BOMBMODEL_H
#include <chrono>
#include <iostream>
class BombModel {
private:
    float x;
    float y;
    float size;
    float maxY;
    float velocidad;
    bool esperando;
    std::chrono::steady_clock::time_point relojEspera;
    bool eliminado;

public:
    bool llegoMaximo;
    BombModel(float ventanaAncho = 0.0f, float ventanaAlto = 0.0f)
        : x(0.0f), y(ventanaAlto / 20), size(50.0f),
          maxY(ventanaAlto * 7 / 9), velocidad(4.0f),
          llegoMaximo(false), esperando(false), eliminado(false) {}

    void setX(float posX) {
        x = posX;
    }

    void caer() {
        if (!llegoMaximo) {
            if (y < maxY) {
                y += velocidad;
            } else {
                llegoMaximo = true;
                relojEspera = std::chrono::steady_clock::now();
                esperando = true;
            }
        } else {
            if (esperando) {
                std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
                std::chrono::duration<float> elapsed = now - relojEspera;
                if (elapsed.count() >= 5.0f) {
                    esperando = false;
                    llegoMaximo = false;
                    setX(static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX) / (x * 3 / 5)));
                    eliminado = true;
                }
            } else {
                if (y < maxY) {
                    y += velocidad;
                }
            }
        }
    }

    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }

    float getSize() const {
        return size;
    }

    bool isEliminado() const {
        return eliminado;
    }
};

#endif