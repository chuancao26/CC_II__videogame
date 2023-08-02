
#ifndef BOMBVIEW_H
#define BOMBVIEW_H
#include "bombmodel.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class BombView {
private:
    sf::Sprite sprite;
    sf::Texture texturaCae;
    sf::Texture texturaPiso;
    sf::RenderWindow window;

public:
    BombView() {
        if (!texturaCae.loadFromFile("img/nivel_flor/bombaCae.png")) {
            std::cout << "Error al cargar la imagen bombaCae.png" << std::endl;
        }

        if (!texturaPiso.loadFromFile("img/nivel_flor/bombaPiso.png")) {
            std::cout << "Error al cargar la imagen bombaPiso.png" << std::endl;
        }

        sprite.setTexture(texturaPiso);
    }

    void setSize(float size) {
        sprite.setScale(size / texturaPiso.getSize().x*1.2, size / texturaPiso.getSize().y*1.2);
    }

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

    void setTextureCae() {
        sprite.setTexture(texturaCae);
    }

    void setTexturePiso() {
        sprite.setTexture(texturaPiso);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

};

#endif