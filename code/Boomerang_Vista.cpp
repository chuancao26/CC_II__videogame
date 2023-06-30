#include <SFML/Graphics.hpp>
#include <iostream>

class BoomerangView {
private:
    sf::Sprite sprite;
    sf::Texture texture1;
    sf::Texture texture2;


public:
    BoomerangView(float width, float height) {
        // Cargar las texturas desde los archivos
        if (!texture1.loadFromFile("img\\nivel_flor\\boomerang1.png")) {
            // Manejar el error si la carga de la textura 1 falla
            std::cout << "Error al cargar la imagen boomerang1.png" << std::endl;
        }

        if (!texture2.loadFromFile("img\\nivel_flor\\boomerang2.png")) {
            // Manejar el error si la carga de la textura 2 falla
            std::cout << "Error al cargar la imagen boomerang2.png" << std::endl;
        }

        // Establecer la textura inicial en el sprite y ajustar su escala
        sprite.setTexture(texture1);
        sprite.setScale(width / texture1.getSize().x, height / texture1.getSize().y * 1.3);
    }

    void updateTexture(float x) {
        if ((x > 100 && x < 200) || (x > 300 && x < 400) || (x > 500 && x < 600) || (x > 700)) {
            sprite.setTexture(texture1);
        }
        else {
            sprite.setTexture(texture2);
        }
    }

    void draw(sf::RenderWindow& window, float x, float y) {
        sprite.setPosition(x, y);
        window.draw(sprite);
    }
};
