#include <SFML/Graphics.hpp>

class Background {
public:
    Background(sf::RenderWindow& window) : window_(window) {
        if (!texture_.loadFromFile("img\\nivel_flor\\fondoFlor.png")) {
            // Error al cargar la imagen fondoFlor.png
            return;
        }

        sprite_.setTexture(texture_);

        // Escala la imagen para que encaje con el tama�o de la ventana
        float scaleX = static_cast<float>(window.getSize().x) / sprite_.getLocalBounds().width;
        float scaleY = static_cast<float>(window.getSize().y) / sprite_.getLocalBounds().height;
        sprite_.setScale(scaleX, scaleY);
    }

    void draw() {
        window_.draw(sprite_);
    }

private:
    sf::RenderWindow& window_;
    sf::Texture texture_;
    sf::Sprite sprite_;
};