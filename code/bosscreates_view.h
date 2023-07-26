
#ifndef BOSSCREATES_VIEW_H
#define BOSSCREATES_VIEW_H
#include "bosscreates_model.h"
#include <iostream> 

class FlorBossView {
private:
    sf::RenderWindow& window_;
    sf::Texture normal1T;
    sf::Texture normal2T;
    sf::Sprite spriteN1;
    sf::Sprite spriteN2;
    sf::RectangleShape rectThird_;
public:
    FlorBossView(sf::RenderWindow& window) : window_(window) {
        if ((!normal1T.loadFromFile("img\\nivel_flor\\normal1.png")) || (!normal2T.loadFromFile("img\\nivel_flor\\normal2.png"))) {
            // Error al cargar las texturas.
            std::cerr << "Error al cargar las texturas." << std::endl;
        }
        spriteN1.setTexture(normal1T);
        spriteN2.setTexture(normal2T);

        spriteN1.setScale(window.getSize().x / 3 / spriteN1.getLocalBounds().width,
                          ((window.getSize().y * 4) / 5) / spriteN1.getLocalBounds().height);
        spriteN2.setScale(window.getSize().x / 3 / spriteN2.getLocalBounds().width,
                          ((window.getSize().y * 4) / 5) / spriteN2.getLocalBounds().height);

        spriteN1.setPosition(window_.getSize().x - (spriteN1.getLocalBounds().width) / 1.1,
                             window.getSize().y / 12);
        spriteN2.setPosition(window_.getSize().x - (spriteN2.getLocalBounds().width) / 1.1,
                             window.getSize().y / 12);
        normal1T.setSmooth(true);
        normal2T.setSmooth(true);
    }

    void draw(int state) {
        if (state == 1) {
            window_.draw(spriteN1);
        } else if (state == 0) {
            window_.draw(spriteN2);
        }
        window_.draw(rectThird_);
    }

    void removeRectangles() {
        spriteN1.setScale(0.0f, 0.0f);
        spriteN2.setScale(0.0f, 0.0f);
        rectThird_.setSize(sf::Vector2f(0.0f, 0.0f));
    }

    void startGrowing() {

    }
};

#endif