#ifndef THORNSROOT_VIEW_H
#define THORNSROOT_VIEW_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "thornsroot_model.h"

class ThornsRootView {
private:
    sf::RenderWindow& window;
    sf::Texture finalTexture1;
    sf::Texture finalTexture2;
    sf::Texture finalTexture3;
    sf::Texture finalTexture4;
    sf::Texture finalTexture;
    sf::Texture raizEnganchadaTexture;
    sf::Texture raizEnganchadaTexture2;
    sf::RectangleShape raiz;

public:
    ThornsRootView(sf::RenderWindow& window) : window(window) {
        if (!finalTexture1.loadFromFile("final1.png") || !finalTexture2.loadFromFile("final2.png") ||
            !finalTexture3.loadFromFile("final3.png") || !finalTexture4.loadFromFile("final4.png") ||
            !raizEnganchadaTexture2.loadFromFile("espina.png") ||
            !raizEnganchadaTexture.loadFromFile("enganchar.png") || !finalTexture.loadFromFile("final.png")) {
            std::cerr << "Error al cargar las texturas." << std::endl;
        }

        raiz.setSize(sf::Vector2f(window.getSize().x * 3 / 4, window.getSize().y / 3));
        raiz.setPosition(sf::Vector2f(window.getSize().x / 4, window.getSize().y * 2 / 3));
        raiz.setFillColor(sf::Color::Transparent);
    }

    void drawImage(const sf::Texture& texture) {
        sf::Sprite sprite(texture);
        sprite.setPosition(window.getSize().x - (sprite.getLocalBounds().width) / 1.1, window.getSize().y / 12);
        window.clear();
        window.draw(sprite);
        
        window.display();
    }

    void drawRaiz(const sf::Texture& texture, float rectX1, float rectX2, float rectY) {
        sf::Sprite sprite(texture);
        sf::Sprite sprite2(texture);

        sprite.setPosition(sf::Vector2f(rectX1, rectY));
        sprite2.setPosition(sf::Vector2f(rectX2, rectY));

        window.draw(sprite);
        window.draw(sprite2);
    }

    void draw() {
        window.clear();
        window.draw(raiz);
        window.display();
    }
    
 
    
    const sf::Texture& getfinalTexture1() const {
    return finalTexture1;
    }

    const sf::Texture& getfinalTexture2() const {
        return finalTexture2;
    }

    const sf::Texture& getfinalTexture3() const {
        return finalTexture3;
    }

    const sf::Texture& getfinalTexture4() const {
        return finalTexture4;
    }

    const sf::Texture& getfinalTexture() const {
        return finalTexture;
    }

    const sf::Texture& getraizEnganchadaTexture() const {
        return raizEnganchadaTexture;
    }

    const sf::Texture& getraizEnganchadaTexture2() const {
        return raizEnganchadaTexture2;
    }
};

#endif
