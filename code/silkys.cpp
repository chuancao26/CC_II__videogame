#include <SFML/Graphics.hpp>
#include <iostream>

class Silky {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    float limSup;
    float limInf;
    float velocity;
    bool movingUp;

public:
    Silky(float windowHeight, float windowWidth) : limSup(windowHeight / 3.f), limInf(windowHeight / 2.f), velocity(-4.f), movingUp(true) {
        if (!texture.loadFromFile("silky.png")) {
            // Manejo de error si no se puede cargar la textura
        }

        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
        sprite.setPosition(sf::Vector2f(windowWidth * 2.f / 3.f, windowHeight / 2.f));
    }

    void update() {
        sf::Vector2f position = sprite.getPosition();

        if (movingUp) {
            position.y += velocity;
            position.x += velocity-1.f;
            if (position.y <= limSup) {
                movingUp = false;
                velocity = 4.f;
            }

        } else {
            position.y += velocity;
            position.x -= velocity+1.f;
            if (position.y >= limInf) {
                movingUp = true;
                velocity = -4.f;
            }
        }

        sprite.setPosition(position);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Silky");
    window.setFramerateLimit(60);

    Silky silky(window.getSize().y, window.getSize().x);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        silky.update();

        window.clear();
        silky.draw(window);
        window.display();
    }

    return 0;
}
