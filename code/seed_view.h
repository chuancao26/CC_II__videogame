#ifndef SEED_VIEW_H
#define SEED_VIEW_H

#include <SFML/Graphics.hpp>
#include "seed_model.h"

class SeedView {
private:
    sf::Texture texture;
    sf::Sprite sprite;

public:
    SeedView(const sf::Vector2f& position) {
        if (!texture.loadFromFile("img/nivel_flor/seed.png")) {
            // Manejo de error si no se puede cargar la textura
        }

        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
        sprite.setPosition(position);
    }

    void updatePosition(const sf::Vector2f& position) {
        sprite.setPosition(position);
    }

    void draw(sf::RenderWindow& window, float angle) {
        sprite.setRotation(angle);
        window.draw(sprite);
    }
    sf::Sprite& getSprite()
    {
        return sprite; 
    }
};

#endif